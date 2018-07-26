#ifndef RAFT_PROJ_FOLLOWER_H
#define RAFT_PROJ_FOLLOWER_H

#include "identity_base.h"
#include "common.h"

namespace SJTU {

	/// implements identity_base abstract class.
	class Follower : IdentityBase {
	public:
		explicit Follower(State &state, Timer &timer, std::function<void(IdentityNo)> transformer) :
				IdentityBase(state, timer, transformer) {}

		~Follower() override;

//		CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest) override;

//		CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest) override;

		void init() override;

		void leave() override;

		void TimeOutFunc() override;
	};
};

#endif //RAFT_PROJ_FOLLOWER_H
