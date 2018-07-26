#include <cstdio>
#include "raft/identities/identity_base.h"

namespace SJTU {
	/**
	 * Implement default AppendEntries receiver behaviour described in paper.
	 *
	 * Each implementation comprises of two parts: generating reply and perform actual action to receiver itself.
	 * */
	CppAppendEntriesResponse IdentityBase::ProcsAppendEntriesFunc(SJTU::CppAppendEntriesRequest request) {
//		CppAppendEntriesResponse response;
//		response.term = state.currentTerm; 	/// for leader to update itself.
//
//		if(request.term < state.currentTerm)
//			response.success = false;
//
//		if(state.logs[request.prevLogIndex].term != request.prevLogTerm)
//			response.success = false;

		CppAppendEntriesResponse response;
		response.success = true;
		response.term = state_.currentTerm;
		printf("default appendEntriesFunc is called\n");
		return response;
	}

	/**
	 * This function is concerned with code review, which deals with voting.
	 * But I don't remember the meaning of up-to-date.
	 * */
	CppRequestVoteResponse IdentityBase::ProcsRequestVoteFunc(SJTU::CppRequestVoteRequest request) {
		CppRequestVoteResponse response;
		response.voteGranted = true;
		response.term = state_.currentTerm;
		printf("default requestVoteFunc is called\n");

		/// real implementation.
//		if(request.term < state.currentTerm)
//			response.voteGranted = false;
		/// check whether the candidate's log is up-to-date.
		return response;
	}
};