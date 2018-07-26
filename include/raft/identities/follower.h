#ifndef RAFT_PROJ_FOLLOWER_H
#define RAFT_PROJ_FOLLOWER_H

#include "identity_base.h"

namespace SJTU {

	/// implements identity_base abstract class.
	class Follower : IdentityBase {
	public:
		explicit Follower(State &state) : IdentityBase(state) {}

		~Follower() override;

		CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest) override;

		CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest) override;

		void TimeOutFunc() override;
	};
};

#endif //RAFT_PROJ_FOLLOWER_H
