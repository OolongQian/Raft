#include "raft/raft.h"
#include "raft/event_queue/event_queue.h"
#include "raft/timer/timer.h"
#include "raft/state.h"
#include "raft/raft_proto/raft_peer_client.h"

#include "raft/identities/follower.h"
#include "raft/identities/candidate.h"
#include "raft/identities/leader.h"

#include <iostream>
#include <vector>
#include <raft/raft_rpc/raft_server.h>

namespace SJTU {
	struct Raft::Impl {
		explicit Impl(const ServerInfo &info);

		EventQueue eventQueue_;
		Timer timer_;
		State state_;

		std::unique_ptr<IdentityBase> identities_[IdentityNum];
		int currentIdentity_;

		/**
		 * This structure is a little naked, reconstruct it later on.
		 * */
		RaftServer server_end_;                          /// opens up a single server_end waiting for others' requests.
		std::vector<RaftPeerClientImpl> client_ends_;    /// opens up multiple client_ends_, number of which depends on config.

		const ServerInfo &info;
	};

	Raft::Impl::Impl(const SJTU::ServerInfo &info) : info(info) {
		identities_[FollowerNo] = std::make_unique<Follower>();
		identities_[CandidateNo] = std::make_unique<Candidate>();
		identities_[LeaderNo] = std::make_unique<Leader>();
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
};

namespace SJTU {
	Raft::Raft(const ServerInfo &info) : pImpl(std::make_unique<Impl>(info)) {}

	Raft::~Raft() = default;

	void Raft::init() {
		printf("raft is initting...\n");
		printf("raft is binding terminate action...\n");

		pImpl->timer_.BindPushEvent(std::bind(&EventQueue::addEvent, &pImpl->eventQueue_, std::placeholders::_1));
		pImpl->timer_.BindTimeOutAction([] {
			std::cout << "timer's terminate action is triggered" << std::endl;
		});

//		pImpl->timer_.BindTimeOutAction(std::bind(&EventQueue::addEvent, &pImpl->eventQueue_, [] {
//			std::cout << "timer's terminate action is triggered" << std::endl;
//		}));
	}

	void Raft::Start() {
		pImpl->eventQueue_.Start();
		pImpl->timer_.Start();
	}

	void Raft::Stop() {
		pImpl->eventQueue_.Stop();
		pImpl->timer_.Stop();
	}
};