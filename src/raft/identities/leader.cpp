#include "../../../include/raft/identities/leader.h"
#include "../../../include/raft/raft_proto/raft_peer.pb.h"

#define _NOT_TRIVIAL_REQUEST

namespace SJTU {

Leader::~Leader() {

}

void Leader::init() {
#ifndef _NOLOG
	printf("init to be leader...\n");
#endif
	++state_.currentTerm;
	timer_.SetTimeOut(info.get_electionTimeout() / 2, info.get_electionTimeout() / 2);
	timer_.Start();
	state_.votedFor.clear();

	for (const ServerId &id : info.get_srvList()) {
		int a = state_.log.back().entryIndex + 1;
		state_.nextIndex[id] = state_.log.back().entryIndex + 1;    /// init to be leader's last log index + 1.
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
			PbAppendEntriesRequest request;


			size_t last_entryindex_cache = MakeHeartBeat(client_ends_[i]->id, &request);

			PbAppendEntriesResponse response;
			grpc::ClientContext context;

#ifndef _NOLOG
			printf("Leader sends out request to other server...\n");
#endif

			context.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(30));
			client_ends_[i]->stub_->AppendEntriesRPC(&context, request, &response);

#ifndef _NOLOG
			printf("Leader received response from other server...\n");
			printf("id %s, it says: term %lld, success %d\n", client_ends_[i]->id.toString().c_str(), response.term(),
						 int(response.success()));
#endif
			if (response.success()) {
				printf("appendEntries success, update nextIndex and matchIndex\n");
				std::cerr << "deleted leader response for heartbeat" << std::endl;

				boost::unique_lock<boost::mutex> lk(state_.map_mtx);
				long long &matchIndex = state_.matchIndex[client_ends_[i]->id];
				long long &nextIndex = state_.nextIndex[client_ends_[i]->id];
				matchIndex = (long long) last_entryindex_cache;
				nextIndex = matchIndex + 1;
				lk.unlock();
				fprintf(stderr, "id: %s, change nextIndex %d\n", client_ends_[i]->id.toString().c_str(),
								state_.nextIndex[client_ends_[i]->id]);

				CheckCommitIndexUpdate();
				fprintf(stderr, "leader's commitIndex is %d\n", state_.commitIndex);
			} else if (response.inconsist()) {
				printf("appendEntries fail because of log inconsistency, decrement nextIndex and retry\n");

				boost::unique_lock<boost::mutex> lk(state_.map_mtx);
				long long &nextIndex = state_.nextIndex[client_ends_[i]->id];
				--nextIndex;
				lk.unlock();
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

size_t Leader::MakeHeartBeat(const ServerId &id, PbAppendEntriesRequest *request) {
	request->set_term(state_.currentTerm);
	request->set_leaderid(info.get_local().toString());
	long long nxtIdx = state_.nextIndex.at(id);
	fprintf(stderr, "id: %s, nextIndex %d\n", id.toString().c_str(), nxtIdx);
	request->set_prevlogindex(
			state_.log.at(nxtIdx - 1).entryIndex);  // previous log index is which immediately proceed the new ones.
	request->set_prevlogterm(state_.log.at(nxtIdx - 1).term);
	size_t last_index = state_.log.length();
	for (long long i = nxtIdx; i <= last_index; ++i) {
		PbAppendEntriesRequest_Entry *entry = request->add_entries();
		const Entry log_entry = state_.log.at(i);
		entry->set_term(log_entry.term);
		entry->set_key(log_entry.key);
		entry->set_val(log_entry.val);
		entry->set_command(log_entry.command);
		entry->set_entryindex(i);
		entry->set_replyerid(log_entry.replyerId);
		entry->set_prmindex(log_entry.prmIndex);
	}
	request->set_leadercommit(state_.commitIndex);
	return last_index;
}


/**
 * See the last entry of description for leaders in paper.
 * */

void Leader::CheckCommitIndexUpdate() {
	long long checked_N = -1;
	long long cur_N = state_.commitIndex + 1;
	int cnt = 1;

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
		if (cnt > (info.get_srvList().size()) / 2) checked_N = cur_N;
		++cur_N;
	}
	if (checked_N == -1) {
		printf("useless N check\n");
	} else {
		state_.commitIndex = checked_N;
		apply_queue.notify();
		printf("useful N check, set commitIndex to be %lld\n", state_.commitIndex);
	}
}

void Leader::ProcsAppendEntriesFunc(const PbAppendEntriesRequest *request, PbAppendEntriesResponse *response) {
	IdentityBase::ProcsAppendEntriesFunc(request, response);
	printf("leader hears himself's heartbeat\n");
	if (request->term() > state_.currentTerm) {
		state_.currentTerm = request->term();
		state_.votedFor.clear();
		identity_transformer(FollowerNo);
	} else {
		timer_.Reset();
	}
}

void Leader::ProcsRequestVoteFunc(const PbRequestVoteRequest *request, PbRequestVoteResponse *response) {
	IdentityBase::ProcsRequestVoteFunc(request, response);
	if (request->term() > state_.currentTerm) {
		state_.currentTerm = request->term();
		state_.votedFor.clear();
		identity_transformer(FollowerNo);
	} else {
		timer_.Reset();
	}
}

void Leader::ProcsPutFunc(const PbPutRequest *request, PbPutResponse *response) {
	if (request->senderid().empty()) {
		ProcsClientPutFunc(request, response);
	} else {
		ProcsPeerPutFunc(request, response);
	}
}

void Leader::ProcsClientPutFunc(const PbPutRequest *request, PbPutResponse *response) {
	Entry log;
	log.term = state_.currentTerm;
	log.command = "Put";
	log.key = request->key();
	log.val = request->val();
	log.entryIndex = state_.log.back().entryIndex + 1;
	log.replyerId = info.get_local().toString();
	log.prmIndex = state_.prmRepoIdx++;

	std::promise<std::string> prm;
	std::future<std::string> fut = prm.get_future();
	state_.prmRepo.insert(std::pair<long long, std::promise<std::string> >(log.prmIndex, std::move(prm)));
	fprintf(stderr, "pushback, log size is %d\n", state_.log.length());
	state_.log.pushBack(log);

	response->set_replymsg(fut.get());
	response->set_success(true);
}

void Leader::ProcsPeerPutFunc(const PbPutRequest *request, PbPutResponse *response) {
	;
}
};
