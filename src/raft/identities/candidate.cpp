#include "raft/identities/candidate.h"

namespace SJTU {
	void Candidate::TimeOutFunc() {
		printf("invoke candidate's timeout Func\n");
		identity_transformer(CandidateNo);
	}
};