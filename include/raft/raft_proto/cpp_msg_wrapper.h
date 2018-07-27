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
#include "raft_peer.pb.h"

namespace SJTU {
	struct CppAppendEntriesRequest {
		int term;
		int leaderId;
		int prevLogIndex;
		int prevLogTerm;
		Log *entries;
		int leaderCommit;

		CppAppendEntriesRequest() = default;

		explicit CppAppendEntriesRequest(PbAppendEntriesRequest) {
			;
		}

		PbAppendEntriesRequest Convert() {
			return PbAppendEntriesRequest();
		}
	};

	struct CppAppendEntriesResponse {
		int term;
		bool success;

		CppAppendEntriesResponse() = default;

		explicit CppAppendEntriesResponse(PbAppendEntriesResponse) {
			;
		}

		PbAppendEntriesResponse Convert() {
			return PbAppendEntriesResponse();
		}
	};

	struct CppRequestVoteRequest {
		int term;
		int candidateId;
		int lastLogIndex;
		int lastLogTerm;

		CppRequestVoteRequest() = default;

		explicit CppRequestVoteRequest(PbRequestVoteRequest) {
			;
		}

		PbRequestVoteRequest Convert() {
			return PbRequestVoteRequest();
		}
	};

	struct CppRequestVoteResponse {
		int term;
		bool voteGranted;

		CppRequestVoteResponse() = default;

		explicit CppRequestVoteResponse(PbRequestVoteResponse) {
			;
		}

		PbRequestVoteResponse Convert() {
			return PbRequestVoteResponse();
		}
	};
};

#endif //RAFT_PROJ_CPP_MSG_WRAPPER_H
