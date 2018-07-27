#include <future>
#include "../../../include/raft/identities/candidate.h"
#include "../../../include/raft/raft_proto/raft_peer_service.h"

namespace SJTU {
	Candidate::~Candidate() {}

	void Candidate::init() {
		++state_.currentTerm;
		RequestVote();
	}

	void Candidate::leave() {}

	void Candidate::TimeOutFunc() {}

	void Candidate::RequestVote() {
		for (int i = 0; i < client_ends_.size(); ++i) {
			client_ends_[i].th = boost::thread([this] {
				PbRequestVoteRequest request = MakeVoteRequest();
				PbRequestVoteResponse response;
				grpc::ClientContext context;
				client_ends_[i].stub_->RequestVoteRPC(&context, request, &response);
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
		CppRequestVoteRequest request(state_.currentTerm, info.get_local(), state_.logs.size() - 1,
																	state_.logs.back().term);
		return request.Convert();
	}
};
