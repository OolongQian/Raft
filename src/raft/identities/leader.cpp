#include "../../../include/raft/identities/leader.h"

//#define _NOT_TRIVIAL_REQUEST

namespace SJTU {

	Leader::~Leader() {

	}

	void Leader::init() {
#ifndef _NOLOG
		printf("init to be leader...\n");
#endif
		timer_.SetTimeOut(info.get_electionTimeout() / 2);
		timer_.Start(true);
		++state_.currentTerm;
		state_.votedFor.clear();

		for (const ServerId &id : info.get_srvList()) {
			if (id == info.get_local()) continue;
			state_.nextIndex[id] = state_.log.back().entryIndex;    /// init to be leader's last log index + 1.
			state_.matchIndex[id] = 0;                        /// init to be 0, increase monotonically.
		}

		transforming = false;
	}

	void Leader::leave() {
		transforming = true;

		std::cerr << "clear votedFor record" << std::endl;
		state_.votedFor.clear();
#ifndef _NOLOG
		printf("leaving leader...shutting down all threads and client ends\n");
		printf("leaving leader...stop leader heartbeat\n");
#endif
		for (size_t i = 0; i < client_ends_.size(); ++i) {
			if (client_ends_[i]->th.joinable()) {
				client_ends_[i]->th.interrupt();
				client_ends_[i]->th.join();
			}
		}
		timer_.Stop();
	}

	void Leader::TimeOutFunc() {
		SendHeartBeat();
		CheckCommitIndexUpdate();
	}

	void Leader::SendHeartBeat() {

		/**
		 * Join by bruteforce.
		 * */
		for (size_t i = 0; i < client_ends_.size(); ++i) {
			if (client_ends_[i]->th.joinable())
				client_ends_[i]->th.join();
		}
		for (size_t i = 0; i < client_ends_.size(); ++i) {
			client_ends_[i]->th = boost::thread([this, i]() mutable {
				PbAppendEntriesRequest request = MakeHeartBeat(client_ends_[i]->id);

				PbAppendEntriesResponse response;
				grpc::ClientContext context;

#ifndef _NOLOG
				printf("Leader sends out request to other server...\n");
#endif

				context.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(30));
				client_ends_[i]->stub_->AppendEntriesRPC(&context, request, &response);      /// this line has serious problems.

#ifndef _NOLOG
				printf("Leader received response from other server...\n");
				printf("it says: term %lld, success %d\n", response.term(), int(response.success()));
#endif
				if (response.success()) {
					printf("appendEntries success, update nextIndex and matchIndex\n");
					std::cerr << "deleted leader response for heartbeat" << std::endl;
//					long long &matchIndex = state_.matchIndex[client_ends_[i]->id];
//					long long &nextIndex = state_.nextIndex[client_ends_[i]->id];
//					long long lastEntryIndex = request.entries(request.entries_size() - 1).entryindex();
//					matchIndex = lastEntryIndex;
//					nextIndex = matchIndex + 1;
				} else {
					printf("appendEntries fail, decrement nextIndex and retry\n");
					std::cerr << "deleted leader response for heartbeat" << std::endl;
//					long long &nextIndex = state_.nextIndex[client_ends_[i]->id];
//					--nextIndex;
				}

				if (state_.currentTerm < response.term()) {
					printf("leader term smaller than other server, transform to follower...\n");
					fprintf(stderr, "leader transform to follower, asynchronous disaster may happen.\n");
					state_.currentTerm = response.term();
					state_.votedFor.clear();
					identity_transformer(FollowerNo);
				}
			});
		}
	}

	PbAppendEntriesRequest Leader::MakeHeartBeat(const ServerId &id) {
		boost::lock_guard<boost::mutex> lk(mtx_);
#ifndef _NOLOG
		printf("current server's log is empty, initialize a trivial request...\n");
#endif

		/**
		 * If last log index >= nextIndex for a follower: send AppendEntries RPC with log entries starting at
		 * nextIndex.
		 * */
		std::vector<Entry> append_entries;
		append_entries.clear();
#ifdef _NOT_TRIVIAL_REQUEST
		if (state_.log.back().entryIndex >= state_.nextIndex.at(id)) {
			for (long long i = state_.nextIndex.at(id); i <= state_.log.back().entryIndex; ++i) {
				append_entries.push_back(state_.log.at(i));
			}
		}
#endif
		CppAppendEntriesRequest request(state_.currentTerm, info.get_local().toString(), 0, -1, std::move(append_entries),
																		state_.commitIndex);
//		request.set_term(state_.currentTerm);
//		request.set_leaderid(info.get_local().toString());
//		request.set_prevlogindex(0);
//		request.set_prevlogterm(-1);
//		request.set_entries(-1);	/// this should be optional.
//		request.set_leadercommit(state_.commitIndex);
		return request.Convert();
	}

	/**
	 * See the last entry of description for leaders in paper.
	 * */

	void Leader::CheckCommitIndexUpdate() {
		long long checked_N = -1;
		long long cur_N = state_.commitIndex + 1;
		int cnt = 0;

		while (cur_N <= state_.log.back().entryIndex) {
			if (state_.log.at(cur_N).term < state_.currentTerm) {
				++cur_N;
				continue;
			} else if (state_.log.at(cur_N).term > state_.currentTerm) {
				break;
			}

			for (const ServerId &id : info.get_srvList()) {
				if (id == info.get_local()) continue;
				if (state_.matchIndex.at(id) >= cur_N)
					++cnt;
			}
			if (cnt > (info.get_srvList().size() - 1) / 2) checked_N = cur_N;
			++cur_N;
		}
		if (checked_N == -1) {
			printf("useless N check\n");
		} else {
			state_.commitIndex = checked_N;
			printf("useful N check, set commitIndex to be %lld\n", state_.commitIndex);
		}
	}
};