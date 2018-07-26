#ifndef RAFT_PROJ_IDENTITY_BASE_H
#define RAFT_PROJ_IDENTITY_BASE_H

#include "raft/raft_proto/cpp_msg_wrapper.h"
#include "raft/state.h"

namespace SJTU {
	/**
	 * A base class
	 * */
	class IdentityBase {
	public:

		explicit IdentityBase(State &state) : state(state) {}

		virtual ~IdentityBase() = default;

		/// define two pure virtual functions.
		/// look up virtual functions' definitions clearly.
		virtual CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest);

		virtual CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest);

		virtual void TimeOutFunc() = 0;

	private:
		State &state;
	};
};
#endif //RAFT_PROJ_IDENTITY_BASE_H
