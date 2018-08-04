#include "../../../include/raft/identities/follower.h"

namespace SJTU {

	Follower::~Follower() {
	}

	void Follower::init() {
#ifndef _NOLOG
		printf("init to be follower...\n");
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
		identity_transformer(CandidateNo);
	}

	void Follower::ProcsAppendEntriesFunc(const PbAppendEntriesRequest *request, PbAppendEntriesResponse *response) {
		IdentityBase::ProcsAppendEntriesFunc(request, response);
		/// if commitIndex > lastApplied: increment lastApplied, apply log[lastApplied] to state machine.
		/// oh I suddenly realize that this should be automated by apply_queue!!!
		if (request->term() > state_.currentTerm) {
			state_.currentTerm = request->term();
			state_.votedFor.clear();
		}
		identity_transformer(FollowerNo);
	}

	void Follower::ProcsRequestVoteFunc(const PbRequestVoteRequest *request, PbRequestVoteResponse *response) {
		if(request->term() > state_.currentTerm)
			state_.votedFor.clear();
		IdentityBase::ProcsRequestVoteFunc(request, response);
		if (request->term() > state_.currentTerm) {
			state_.currentTerm = request->term();
		}
		identity_transformer(FollowerNo);
	}

	/*
	void Follower::AppendEntriesSelfModification(const PbAppendEntriesRequest *request) {
		printf("follower receives appendEntry\n");
		if (request->term() > state_.currentTerm) {
			state_.currentTerm = request->term();
			state_.votedFor.clear();
			identity_transformer(FollowerNo);
		}
		else {
			printf("follower to follower\n");
			identity_transformer(FollowerNo);
		}
	}
	 */

//	void Follower::RequestVoteSelfModification(const PbRequestVoteRequest *request) {
//		;
//	}
};