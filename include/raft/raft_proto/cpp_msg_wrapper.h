#ifndef RAFT_PROJ_CPP_MSG_WRAPPER_H
#define RAFT_PROJ_CPP_MSG_WRAPPER_H

/**
 * We have defined rpc calls in proto files, and protocol compiler helps
 * us generate interfaces for those msg classes, but they are still difficult
 * to use and cannot serve as a data wrapper inside our raft implementation.
 *
 * Therefore we had better create such data wrappers in cpp version and define
 * some functions to convert between them.
 * */
#include "../../log/log.h"

namespace SJTU {
	struct CppAppendEntriesRequest {
		int term;
		int leaderId;
		int prevLogIndex;
		int prevLogTerm;
		Log *entries;
		int leaderCommit;

		CppAppendEntriesRequest() = default;
	};

	struct CppAppendEntriesResponse {
		int term;
		bool success;

		CppAppendEntriesResponse() = default;
	};

	struct CppRequestVoteRequest {
		int term;
		int candidateId;
		int lastLogIndex;
		int lastLogTerm;

		CppRequestVoteRequest() = default;
	};

	struct CppRequestVoteResponse {
		int term;
		bool voteGranted;

		CppRequestVoteResponse() = default;
	};
};

#endif //RAFT_PROJ_CPP_MSG_WRAPPER_H
