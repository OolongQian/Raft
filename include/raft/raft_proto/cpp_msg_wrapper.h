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

namespace SJTU {
	struct CppAppendEntriesRequest {
	};
	struct CppAppendEntriesResponse {
	};
	struct CppRequestVoteRequest {
	};
	struct CppRequestVoteResponse {
	};
};

#endif //RAFT_PROJ_CPP_MSG_WRAPPER_H
