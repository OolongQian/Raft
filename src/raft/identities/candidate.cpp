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
//		std::vector<std::future<PbRequestVoteResponse> >
//		for (int i = 0; i < client_ends_.size(); ++i) {
//
//			PbRequestVoteRequest request;
//			request = MakeRequest();
//			grpc::ClientContext context;
//			client_ends_[i].stub_
//		}
	}
};
