#include <future>
#include "../../../include/raft/identities/candidate.h"
#include "../../../include/raft/raft_proto/raft_peer_service.h"

// #define  _NOLOG

namespace SJTU {
	Candidate::~Candidate() {}

	void Candidate::init() {
#ifndef _NOLOG
		printf("init to be candidate...\n");
#endif
		timer_.SetTimeOut(rand() % (info.get_electionTimeout()) + info.get_electionTimeout());
		timer_.Start(false);
		++state_.currentTerm;
#ifndef _NOLOG
		printf("client_end size: %lu\n", client_ends_.size());
		printf("vote for himself...\n");
#endif
//		++votesReceived;
		votesReceived = 1;
		RequestVote();
	}

	void Candidate::leave() {
#ifndef _NOLOG
		printf("leaving candidate...shutting down all threads and client ends\n");
		printf("leaving candidate...stop candidate timer\n");
#endif
		for (size_t i = 0; i < client_ends_.size(); ++i) {
			if (client_ends_[i]->th.joinable()) {
				client_ends_[i]->th.interrupt();
				client_ends_[i]->th.join();
			}
		}
		transforming = false;
		timer_.Stop();
	}

	/**
	 * This function is pushed by timer into event queue instead of executing by timer.
	 * */
	void Candidate::TimeOutFunc() {
		identity_transformer(CandidateNo);
	}

	void Candidate::RequestVote() {
//		for (int i = 0; i < client_ends_.size(); ++i) {
		for (size_t i = 0; i < client_ends_.size(); ++i) {
			client_ends_[i]->th = boost::thread([this, i]() mutable {
				PbRequestVoteRequest request = MakeVoteRequest();

				PbRequestVoteResponse response;
				grpc::ClientContext context;
#ifndef _NOLOG
				printf("Candidate sends out request to other server...\n");
#endif
				context.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(500));
				client_ends_[i]->stub_->RequestVoteRPC(&context, request, &response);      /// this line has serious problems.

#ifndef _NOLOG
				printf("Candidate received response from other server...\n");
				printf("it says: term %lld, requestVote %d\n", response.term(), int(response.votegranted()));
#endif
				if (response.votegranted()) ++votesReceived;

				if (transforming) {
#ifndef _NOLOG
					printf("There has been one identical transformation task undergoing... returning..\n");
#endif
				}
				if (votesReceived > info.get_srvList().size() / 2 && !transforming) {
					transforming = true;
#ifndef _NOLOG
					printf("There are %lu servers in total. More than half votes received, start to transform to leader...\n",
								 info.get_srvList().size());
					printf("transforming to leader\n");
#endif
					/**
					 * Because transformation invokes .interruption(), after it there cannot be any call to transform identity.
					 * */
					try {
						boost::this_thread::interruption_point();
						identity_transformer(LeaderNo);
					}
					catch (boost::thread_interrupted &) {
						printf("candidate requestVotes thread being interrupted, returning...\n");
						return;
					}
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

