#include "raft/identities/leader.h"

namespace SJTU {
	void Leader::TimeOutFunc() {
		printf("invoke leader's timeout Func\n");
	}
};