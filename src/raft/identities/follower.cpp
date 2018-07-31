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

		transforming = false;
	}

	void Follower::leave() {
		transforming = true;

		timer_.Stop();
	}

	void Follower::TimeOutFunc() {
		identity_transformer(CandidateNo);
	}

	void Follower::AppendEntriesSelfModification(const CppAppendEntriesRequest &) {
		;
	}

	void Follower::RequestVoteSelfModification(const CppRequestVoteRequest &) {
		;
	}
};