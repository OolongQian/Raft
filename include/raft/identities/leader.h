#ifndef RAFT_PROJ_LEADER_H
#define RAFT_PROJ_LEADER_H

#include "identity_base.h"

namespace SJTU {

	/// implements identity_base abstract class.
	class Leader : IdentityBase {
	public:
		explicit Leader(State &state) : IdentityBase(state) {}

		~Leader() override;

		CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest) override;

		CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest) override;

		void TimeOutFunc() override;
	};
};

#endif //RAFT_PROJ_LEADER_H
