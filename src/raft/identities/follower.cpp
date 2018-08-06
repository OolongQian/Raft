#include "../../../include/raft/identities/follower.h"

namespace SJTU {

	Follower::~Follower() {
	}

	void Follower::init() {
#ifndef _NOLOG
//		printf("init to be follower...\n");
#endif
		timer_.SetTimeOut(info.get_electionTimeout(), info.get_electionTimeout() * 2);
		timer_.Start();

		transforming = false;
	}

	void Follower::leave() {
		transforming = true;
		timer_.Stop();
	}

	void Follower::TimeOutFunc() {
//		fprintf(stderr, "server %s transform to candidate becuase of timeout\n", info.get_local().toString().c_str());
		identity_transformer(CandidateNo);
	}

};