#ifndef RAFT_PROJ_LEADER_H
#define RAFT_PROJ_LEADER_H

#include "identity_base.h"

namespace SJTU {

	/// implements identity_base abstract class.
	class Leader : IdentityBase {
	public:
		~Leader() override;

		CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest) override;

		CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest) override;
	};
};


#endif //RAFT_PROJ_LEADER_H
