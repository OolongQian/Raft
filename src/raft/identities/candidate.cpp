#include <future>
#include "../../../include/raft/identities/candidate.h"
#include "../../../include/raft/raft_proto/raft_peer_service.h"

namespace SJTU {
	Candidate::~Candidate() {}

	void Candidate::init() {
		++state_.currentTerm;
		printf("client_end size: %lu\n", client_ends_.size());
		RequestVote();
	}

	void Candidate::leave() {}

	void Candidate::TimeOutFunc() {}

	void Candidate::RequestVote() {
//		for (int i = 0; i < client_ends_.size(); ++i) {
		for (int i = 0; i < client_ends_.size(); ++i) {

			client_ends_[i]->th = boost::thread([this, i]() mutable {
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

				if (votesReceived > info.get_srvList().size() / 2) {
#ifndef _NOLOG
					printf("More than half votes received, start to transform to leader...\n");
#endif
					identity_transformer(LeaderNo);
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

	PbRequestVoteRequest Candidate::MakeVoteRequest() {
//		boost::lock_guard<boost::mutex> lk(mtx_);
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
