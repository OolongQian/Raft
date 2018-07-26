#include "raft/raft.h"
#include "raft/event_queue/event_queue.h"
#include "raft/timer/timer.h"
#include "raft/state.h"
#include "raft/raft_proto/raft_peer_client.h"
#include "raft/raft_rpc/raft_server.h"

#include "raft/identities/follower.h"
#include "raft/identities/candidate.h"
#include "raft/identities/leader.h"

#include <iostream>
#include <vector>

namespace SJTU {
	struct Raft::Impl {
		EventQueue eventQueue_;
		Timer timer_;
		State state_;
		int currentIdentity_;

		std::unique_ptr<IdentityBase> identities_[IdentityNum];

		/**
		 * This structure is a little naked, reconstruct it later on.
		 * */
		RaftServer server_end_;                          /// opens up a single server_end waiting for others' requests.
		std::vector<RaftPeerClientImpl> client_ends_;    /// opens up multiple client_ends_, number of which depends on config.

		const ServerInfo &info;

//  ---------------------------------------------------------------------
		explicit Impl(const ServerInfo &info);

		/**
		 * This function simply invokes identity classes' leave and init function.
		 * But during identity transformation, server state changes (pass by reference).
		 * timer is reset (pass by reference. rpc is set out.
		 * Many heavy work is done, I wanna distribute these works to specialized classes,
		 * thus leaving detailed implementation inside identities.
		 * */
		void IdentityTransform(IdentityNo);
	};

	Raft::Impl::Impl(const SJTU::ServerInfo &info) : info(info) {
		identities_[FollowerNo] = std::make_unique<Follower>(state_, timer_, std::bind(&Raft::Impl::IdentityTransform, this,
																																									 std::placeholders::_1));
		identities_[CandidateNo] = std::make_unique<Candidate>(state_, timer_,
																													 std::bind(&Raft::Impl::IdentityTransform, this,
																																		 std::placeholders::_1);
		identities_[LeaderNo] = std::make_unique<Leader>(state_, timer_, std::bind(&Raft::Impl::IdentityTransform, this,
																																							 std::placeholders::_1);
		currentIdentity_ = FollowerNo;

		/// initialize this many client_ends_...
		for (const ServerId &srv_id : info.get_srvList()) {
			auto channel = grpc::CreateChannel(srv_id.get_port(), grpc::InsecureChannelCredentials());
			client_ends_.emplace_back(channel);
		}

		/// initialize server_end_ implementation functions and run the server.
		auto rqsVtFunc = std::bind(&IdentityBase::ProcsRequestVoteFunc, &identities_[currentIdentity_],
															 std::placeholders::_1);
		auto apdEtyFunc = std::bind(&IdentityBase::ProcsAppendEntriesFunc, &identities_[currentIdentity_],
																std::placeholders::_1);
		server_end_.BindServiceFunc(rqsVtFunc, apdEtyFunc);
		server_end_.AsycRun();
	}

	void Raft::Impl::IdentityTransform(IdentityNo identityNo) {
		identities_[currentIdentity_]->leave();
		currentIdentity_ = identityNo;
		identities_[currentIdentity_]->init();
	}
};

namespace SJTU {
	Raft::Raft(const ServerInfo &info) : pImpl(std::make_unique<Impl>(info)) {}

	Raft::~Raft() = default;

	void Raft::init() {
		;
//		printf("raft is initting...\n");
//		printf("raft is binding terminate action...\n");
//
//		pImpl->timer_.BindPushEvent(std::bind(&EventQueue::addEvent, &pImpl->eventQueue_, std::placeholders::_1));
//		pImpl->timer_.BindTimeOutAction([] {
//			std::cout << "timer's terminate action is triggered" << std::endl;
//		});

//		pImpl->timer_.BindTimeOutAction(std::bind(&EventQueue::addEvent, &pImpl->eventQueue_, [] {
//			std::cout << "timer's terminate action is triggered" << std::endl;
//		}));
	}

	void Raft::Start() {

		/// these are test code, timer_ should be set or reset inside other functions I think...
		/**
		 * I just haven't sorted out how to organize identity transformation synchronously.
		 * Why not just transform myself to candidate right here right now?
		 * */


//		pImpl->eventQueue_.Start();
//		pImpl->timer_.Start();
	}

	void Raft::Stop() {
//		pImpl->eventQueue_.Stop();
//		pImpl->timer_.Stop();
	}
};