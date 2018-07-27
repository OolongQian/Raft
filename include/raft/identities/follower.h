#ifndef RAFT_PROJ_FOLLOWER_H
#define RAFT_PROJ_FOLLOWER_H

#include "identity_base.h"

namespace SJTU {

	/// implements identity_base abstract class.
	class Follower : public IdentityBase {
	public:
//		explicit Follower(State &state, Timer &timer, std::function<void(int)> transformer) :
//		state_(state), timer_(timer), identity_transformer(transformer) {}
//		Follower() : IdentityBase() {}
		explicit Follower(State &state, Timer &timer, std::function<void(int)> transformer,
											std::vector<std::unique_ptr<RaftPeerClientImpl> > &client_ends, const ServerInfo &info) :
				IdentityBase(state, timer, std::move(transformer), client_ends, info) {}

		~Follower() override;

//		CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest) override;

//		CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest) override;

		void init() override;

		void leave() override;

		void TimeOutFunc() override;
	};
};

#endif //RAFT_PROJ_FOLLOWER_H
