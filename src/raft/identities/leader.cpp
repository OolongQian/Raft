#include "../../../include/raft/identities/leader.h"

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
	}

	void Leader::leave() {
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
				PbAppendEntriesRequest request = MakeHeartBeat();

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
			});
		}
	}

	PbAppendEntriesRequest Leader::MakeHeartBeat() {
		boost::lock_guard<boost::mutex> lk(mtx_);
#ifndef _NOLOG
		printf("current server's log is empty, initialize a trivial request...\n");
#endif
		std::vector<CppLogEntry> vec_tmp(0);
		CppAppendEntriesRequest request(state_.currentTerm, info.get_local().toString(), 0, -1, vec_tmp,
																		state_.commitIndex);
//		request.set_term(state_.currentTerm);
//		request.set_leaderid(info.get_local().toString());
//		request.set_prevlogindex(0);
//		request.set_prevlogterm(-1);
//		request.set_entries(-1);	/// this should be optional.
//		request.set_leadercommit(state_.commitIndex);
		return request.Convert();
	}
};