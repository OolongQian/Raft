#ifndef RAFT_PROJ_CANDIDATE_H
#define RAFT_PROJ_CANDIDATE_H

#include "identity_base.h"
#include "boost/atomic.hpp"

namespace SJTU {

	/// implements identity_base abstract class.
	class Candidate : public IdentityBase {
	public:
		explicit Candidate(State &state, Timer &timer, std::function<void(int)> transformer,
											 std::vector<std::unique_ptr<RaftPeerClientImpl> > &client_ends, const ServerInfo &info,
											 ApplyQueue &apply_queue) :
				IdentityBase(state, timer, std::move(transformer), client_ends, info, apply_queue), votesReceived(0) {}

		~Candidate() override;

//		void ProcsAppendEntriesFunc(const PbAppendEntriesRequest *, PbAppendEntriesResponse *) override;

//		void ProcsRequestVoteFunc(const PbRequestVoteRequest *, PbRequestVoteResponse *) override;

//		CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest) override;

//		CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest) override;

		void init() override;

		void leave() override;

		void TimeOutFunc() override;

		void RequestVote();

		PbRequestVoteRequest MakeVoteRequest();

	private:
		boost::atomic<std::size_t> votesReceived{0};
		boost::mutex mtx_;
	};
};

#endif //RAFT_PROJ_CANDIDATE_H
