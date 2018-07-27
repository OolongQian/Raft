#include "../../include/raft/raft.h"
#include "../../include/raft/state.h"
#include "../../include/raft/raft_proto/raft_peer_client.h"

//#include "raft/identities/follower.h"
//#include "raft/identities/candidate.h"
//#include "raft/identities/leader.h"

#include <iostream>
#include <vector>
#include "../../include/raft/state.h"
#include "../../include/common.h"
#include "../../include/raft/raft_proto/raft_peer_client.h"
#include "../../include/server_info.h"
#include "../../include/raft/identities/identity_base.h"

namespace SJTU {
	struct Raft::Impl {
		State state_;
//		int currentIdentity_;

		const ServerInfo &info;

		std::unique_ptr<IdentityBase> identities_[IdentityNum];
//		IdentityBase *identities_[IdentityNum];

//  ---------------------------------------------------------------------
		explicit Impl(const ServerInfo &info);

		~Impl();

		/**
		 * This function simply invokes identity classes' leave and init function.
		 * But during identity transformation, server state changes (pass by reference).
		 * timer is reset (pass by reference. rpc is set out.
		 * Many heavy work is done, I wanna distribute these works to specialized classes,
		 * thus leaving detailed implementation inside identities.
		 * */
		void IdentityTransform(IdentityNo);
	};

	Raft::Impl::Impl(const ServerInfo &info) : info(info) {
		std::function<void(int)> transformer = std::bind(&Raft::Impl::IdentityTransform, this, std::placeholders::_1);
		identities_[FollowerNo] = std::make_unique<Follower>(state_, transformer);
		identities_[CandidateNo] = std::make_unique<Candidate>(state_, transformer);
		identities_[LeaderNo] = std::make_unique<Leader>(state_, transformer);
	}

	void Raft::Impl::IdentityTransform(int) {

	}

	Raft::Impl::~Impl() {}

	Raft::Raft(const ServerInfo &info) {

	}

	Raft::~Raft() {

	}

	void Raft::init() {

	}

	void Raft::Start() {

	}

	void Raft::Stop() {

	}
}