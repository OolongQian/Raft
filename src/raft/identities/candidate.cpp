#include "raft/identities/candidate.h"

namespace SJTU {

	/**
	 * Initialize candidate, start a election.
	 * */
	void Candidate::init() {
		printf("Candidate start a election\n");
	}

	void Candidate::TimeOutFunc() {
		printf("invoke candidate's timeout Func\n");
		identity_transformer(CandidateNo);
	}
};