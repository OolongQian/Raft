#include <future>
#include "../../../include/raft/identities/candidate.h"
#include "../../../include/raft/raft_proto/raft_peer_service.h"

namespace SJTU {
	Candidate::~Candidate() {}

	void Candidate::init() {
		++state_.currentTerm;
#ifndef _NOLOG
		printf("client_end size: %lu\n", client_ends_.size());
		printf("vote for himself...\n");
#endif
		++votesReceived;
		RequestVote();
	}

	void Candidate::leave() {
#ifndef _NOLOG
		printf("leaving candidate...shutting down all threads and client ends\n");
#endif
		for (size_t i = 0; i < client_ends_.size(); ++i) {
			if (client_ends_[i]->th.joinable()) {
				client_ends_[i]->th.interrupt();
			}
		}
	}

	void Candidate::TimeOutFunc() {}

	void Candidate::RequestVote() {
//		for (int i = 0; i < client_ends_.size(); ++i) {
		for (size_t i = 0; i < client_ends_.size(); ++i) {
			client_ends_[i]->th = boost::thread([this, i]() mutable {
				try {
					PbRequestVoteRequest request = MakeVoteRequest();

					PbRequestVoteResponse response;
					grpc::ClientContext context;
#ifndef _NOLOG
					printf("Candidate sends out request to other server...\n");
#endif

					client_ends_[i]->stub_->RequestVoteRPC(&context, request, &response);      /// this line has serious problems.

#ifndef _NOLOG
					printf("Candidate received response from other server...\n");
#endif
					if (response.votegranted()) ++votesReceived;

					if (votesReceived >= info.get_srvList().size() / 2) {
#ifndef _NOLOG
						printf("There are %lu servers in total. More than half votes received, start to transform to leader...\n",
									 info.get_srvList().size());
						printf("transforming to leader\n");
#endif
						identity_transformer(LeaderNo);
					}
				}
					/**
					 * Here I catch all kinds of exceptions. So ugly!!!
					 * */
				catch (boost::thread_interrupted) {
					printf("thread is interrupted and returned\n");
					return;
				}
			});
		}
//		std::vector<std::future<PbRequestVoteResponse> >
//		for (int i = 0; i < client_ends_.size(); ++i) {
//
//			PbRequestVoteRequest request;
//			request = MakeRequest();
//			grpc::ClientContext context;
//			client_ends_[i].stub_
//		}
	}

	/**
	 * access inner data member, synchronize it.
	 * */
	PbRequestVoteRequest Candidate::MakeVoteRequest() {
		boost::lock_guard<boost::mutex> lk(mtx_);
		if (state_.logs.empty()) {
#ifndef _NOLOG
			printf("current server's log is empty, initialize a trivial request...\n");
#endif
			CppRequestVoteRequest request(state_.currentTerm, info.get_local(), 0, -1);
			return request.Convert();
		} else {
			CppRequestVoteRequest request(state_.currentTerm, info.get_local(), state_.logs.size() - 1,
																		state_.logs.back().term);
			return request.Convert();
		}
	}
};
