#ifndef RAFT_PROJ_CANDIDATE_H
#define RAFT_PROJ_CANDIDATE_H

#include "identity_common.h"

namespace SJTU {

	/// implements identity_base abstract class.
	class Candidate : IdentityBase {
	public:
//		explicit Candidate(State &state, Timer &timer, std::function<void(int)> transformer) :
//		state_(state), timer_(timer), identity_transformer(transformer) {}

		explicit Candidate(State &state, Timer &timer, std::function<void(int)> transformer) :
				IdentityBase(state, timer, std::move(transformer)) {}

		~Candidate() override;

//		CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest) override;

//		CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest) override;

		void init() override;

		void leave() override;

		void TimeOutFunc() override;
	};
};

#endif //RAFT_PROJ_CANDIDATE_H
