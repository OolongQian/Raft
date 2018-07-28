#include "../../../include/raft/identities/identity_base.h"

namespace SJTU {

	CppAppendEntriesResponse SJTU::IdentityBase::ProcsAppendEntriesFunc(CppAppendEntriesRequest) {
		printf("appendEntriesRequest is received...trivially respond for now\n");
		CppAppendEntriesResponse response;
		response.term = state_.currentTerm;
		response.success = true;
		return response;
	}

	CppRequestVoteResponse SJTU::IdentityBase::ProcsRequestVoteFunc(CppRequestVoteRequest request) {
		CppRequestVoteResponse response;
		response.term = state_.currentTerm;

		response.voteGranted = true;
		if (request.term < state_.currentTerm)
			response.voteGranted = false;
		if (!state_.votedFor.empty() || state_.votedFor == request.candidateId)
			response.voteGranted = false;

		return response;
	}
};