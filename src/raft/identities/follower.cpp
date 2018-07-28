#include "../../../include/raft/identities/follower.h"

namespace SJTU {

	Follower::~Follower() {
	}

	void Follower::init() {
#ifndef _NOLOG
		printf("init to be follower...\n");
#endif
		timer_.SetTimeOut(rand() % (info.get_electionTimeout()) + info.get_electionTimeout());
		timer_.Start(false);
	}

	void Follower::leave() {
		timer_.Stop();
	}

	void Follower::TimeOutFunc() {
		identity_transformer(CandidateNo);
	}
};