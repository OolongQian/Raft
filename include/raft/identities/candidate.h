#ifndef RAFT_PROJ_CANDIDATE_H
#define RAFT_PROJ_CANDIDATE_H

#include "identity_base.h"

namespace SJTU {

	/// implements identity_base abstract class.
	class Candidate : public IdentityBase {
	public:
//		explicit Candidate(State &state, Timer &timer, std::function<void(int)> transformer) :
//		state_(state), timer_(timer), identity_transformer(transformer) {}

//		Candidate() : IdentityBase() {}
		explicit Candidate(State &state, Timer &timer, std::function<void(int)> transformer,
											 std::vector<RaftPeerClientImpl> &client_ends) :
				IdentityBase(state, timer, std::move(transformer), client_ends) {}

		~Candidate() override;

//		CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest) override;

//		CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest) override;

		void init() override;

		void leave() override;

		void TimeOutFunc() override;
	};
};

#endif //RAFT_PROJ_CANDIDATE_H
