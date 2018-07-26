#ifndef RAFT_PROJ_IDENTITY_BASE_H
#define RAFT_PROJ_IDENTITY_BASE_H

#include <raft/raft_proto/cpp_msg_wrapper.h>

namespace SJTU {
	/**
	 * A base class
	 * */
	class IdentityBase {
	public:
		virtual ~IdentityBase() = default;

		/// define two pure virtual functions.
		/// look up virtual functions' definitions clearly.
		virtual CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest) = 0;

		virtual CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest) = 0;
	};
};
#endif //RAFT_PROJ_IDENTITY_BASE_H
