#include "../../include/raft/raft.h"
#include "../../include/raft/state.h"
#include "../../include/raft/raft_rpc/raft_server.h"

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
	using RequestVoteFunc = std::function<CppRequestVoteResponse(CppRequestVoteRequest)>;
	using AppendEntriesFunc = std::function<CppAppendEntriesResponse(CppAppendEntriesRequest)>;

	struct Raft::Impl {
		State state_;
		Timer timer_;
		int currentIdentity_;

		std::unique_ptr<IdentityBase> identities_[IdentityNum];

		/// opens up multiple client_ends_, number of which depends on config.
		std::vector<RaftPeerClientImpl> client_ends_;
		/// because of some strange reason, server_ends_ cannot be copied or ... just use pointers.
		std::vector<std::unique_ptr<RaftServer> > server_ends_;

		const ServerInfo &info;

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

		CppAppendEntriesResponse ProcsAppendEntriesAdapter(CppAppendEntriesRequest);

		CppRequestVoteResponse ProcsRequestVoteAdapter(CppRequestVoteRequest);

		void TimeOutActionAdapter();
	};

	Raft::Impl::Impl(const ServerInfo &info) : info(info) {
		std::function<void(int)> transformer = std::bind(&Raft::Impl::IdentityTransform, this, std::placeholders::_1);

		identities_[FollowerNo] = std::make_unique<Follower>(state_, timer_, transformer, client_ends_);
		identities_[CandidateNo] = std::make_unique<Candidate>(state_, timer_, transformer, client_ends_);
		identities_[LeaderNo] = std::make_unique<Leader>(state_, timer_, transformer, client_ends_);

		/// initialize client_ends_ and server_ends_.
		/// bind server function adapter into server_end_...
		for (const ServerId &srv_id : info.get_srvList()) {
			auto channel = grpc::CreateChannel(srv_id.toString(), grpc::InsecureChannelCredentials());
			client_ends_.emplace_back(channel);

			server_ends_.push_back(std::make_unique<RaftServer>(srv_id));
			server_ends_.back()->BindServiceFunc(std::bind(&Impl::ProcsRequestVoteAdapter, this, std::placeholders::_1),
																					 std::bind(&Impl::ProcsAppendEntriesAdapter, this, std::placeholders::_1));
//			server_ends_.push_back(std::move(RaftServer(srv_id)));
//			server_ends_.emplace_back(srv_id);
//			server_ends_.back().BindServiceFunc(std::bind(&Impl::ProcsRequestVoteAdapter, this, std::placeholders::_1),
//																					std::bind(&Impl::ProcsAppendEntriesAdapter, this, std::placeholders::_1));
		}

		currentIdentity_ = DownNo;

		/**
		 * Timer should be modified so that we can specify what action burstOut at which time.
		 * */
		timer_.BindTimeOutAction(std::bind(&Impl::TimeOutActionAdapter, this));
	}

	void Raft::Impl::IdentityTransform(IdentityNo identityNo) {
		if (currentIdentity_ != DownNo) identities_[currentIdentity_]->leave();
		currentIdentity_ = identityNo;
		identities_[currentIdentity_]->init();
	}

	Raft::Impl::~Impl() {}

	CppAppendEntriesResponse Raft::Impl::ProcsAppendEntriesAdapter(CppAppendEntriesRequest request) {
		return identities_[currentIdentity_]->ProcsAppendEntriesFunc(request);
	}

	CppRequestVoteResponse Raft::Impl::ProcsRequestVoteAdapter(CppRequestVoteRequest request) {
		return identities_[currentIdentity_]->ProcsRequestVoteFunc(request);
	}

	void Raft::Impl::TimeOutActionAdapter() {
		identities_[currentIdentity_]->TimeOutFunc();
	}
};

namespace SJTU {

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