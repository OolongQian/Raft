#ifndef RAFT_PROJ_CANDIDATE_H
#define RAFT_PROJ_CANDIDATE_H

#include "identity_base.h"

namespace SJTU {

	/// implements identity_base abstract class.
	class Candidate : IdentityBase {
	public:
		explicit Candidate(State &state) : IdentityBase(state) {}

		~Candidate() override;

		CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest) override;

		CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest) override;

		void TimeOutFunc() override;
	};
};

#endif //RAFT_PROJ_CANDIDATE_H
