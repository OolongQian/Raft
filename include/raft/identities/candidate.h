#ifndef RAFT_PROJ_CANDIDATE_H
#define RAFT_PROJ_CANDIDATE_H

#include "identity_base.h"
#include "boost/atomic.hpp"

namespace SJTU {

	/// implements identity_base abstract class.
	class Candidate : public IdentityBase {
	public:
//		explicit Candidate(State &state, Timer &timer, std::function<void(int)> transformer) :
//		state_(state), timer_(timer), identity_transformer(transformer) {}

//		Candidate() : IdentityBase() {}
		explicit Candidate(State &state, Timer &timer, std::function<void(int)> transformer,
											 std::vector<RaftPeerClientImpl> &client_ends, const ServerInfo &info) :
				IdentityBase(state, timer, std::move(transformer), client_ends, info), votesReceived(0) {}

		~Candidate() override;

//		CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest) override;

//		CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest) override;

		void init() override;

		void leave() override;

		void TimeOutFunc() override;

		void RequestVote();

		PbRequestVoteRequest MakeVoteRequest();

	private:
		boost::atomic<std::size_t> votesReceived{0};
	};
};

#endif //RAFT_PROJ_CANDIDATE_H
