#include "raft/identities/follower.h"

namespace SJTU {
	void Follower::TimeOutFunc() {
		printf("invoke follower's timeout Func\n");
		identity_transformer(CandidateNo);
	}
};
