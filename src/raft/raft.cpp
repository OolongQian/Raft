#include "../../include/raft/raft.h"
#include "../../include/raft/state.h"
#include "../../include/raft/raft_rpc/raft_server.h"
#include "../../include/raft/synchronous_queue/event_queue.h"

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
#include "../../include/raft/synchronous_queue/apply_queue.h"
#include "../test/debug_context/raft_debug_context.h"

namespace SJTU {
	using RequestVoteFunc = std::function<CppRequestVoteResponse(CppRequestVoteRequest)>;
	using AppendEntriesFunc = std::function<CppAppendEntriesResponse(CppAppendEntriesRequest)>;

	struct Raft::Impl {
		State state_;
		const ServerInfo &info;

		Timer timer_;
		EventQueue eventQueue_;
		ApplyQueue applyQueue_;

		int currentIdentity_;
		std::unique_ptr<IdentityBase> identities_[IdentityNum];

		std::vector<std::unique_ptr<RaftPeerClientImpl> > client_ends_;
		std::unique_ptr<RaftServer> server_end_;

		/// raft algorithm needn't this, while applyQueue_ needs it.
//		std::map<std::string, std::string> &data;
		//  ---------------------------------------------------------------------

		explicit Impl(const ServerInfo &info, std::map<std::string, std::string> &data);

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

	Raft::Impl::Impl(const ServerInfo &info, std::map<std::string, std::string> &data) : info(info),
																																											 applyQueue_(data, state_) {

		/// identity
		std::function<void(int)> transformer = std::bind(&Raft::Impl::IdentityTransform, this, std::placeholders::_1);
		identities_[FollowerNo] = std::make_unique<Follower>(state_, timer_, transformer, client_ends_, info);
		identities_[CandidateNo] = std::make_unique<Candidate>(state_, timer_, transformer, client_ends_, info);
		identities_[LeaderNo] = std::make_unique<Leader>(state_, timer_, transformer, client_ends_, info);
		currentIdentity_ = DownNo;

		/// gRPC server_end
		server_end_ = std::make_unique<RaftServer>(info.get_local());
		server_end_->BindServiceFunc(std::bind(&Impl::ProcsRequestVoteAdapter, this, std::placeholders::_1),
																 std::bind(&Impl::ProcsAppendEntriesAdapter, this, std::placeholders::_1));
		server_end_->PreMonitorInit();

		/// gRPC client_ends
		for (const ServerId &srv_id : info.get_srvList()) {
			if (srv_id == info.get_local()) continue;
			client_ends_.push_back(std::make_unique<RaftPeerClientImpl>(
					grpc::CreateChannel(srv_id.toString(), grpc::InsecureChannelCredentials()), srv_id));
		}

		/// timer
		timer_.BindTimeOutAction(std::bind(&Impl::TimeOutActionAdapter, this));
		timer_.BindPushEvent(std::bind(&EventQueue::addEvent, &eventQueue_, std::placeholders::_1));

		state_.Init();
	}

	Raft::Impl::~Impl() {}

	void Raft::Impl::IdentityTransform(const IdentityNo identityNo) {
		RaftDebugContext &debugContext = GetDebug();
		debugContext.before_tranform(currentIdentity_, identityNo);

		eventQueue_.addEvent([this, identityNo]() mutable {
			if (currentIdentity_ != DownNo)
				identities_[currentIdentity_]->leave();
			currentIdentity_ = identityNo;
			identities_[currentIdentity_]->init();
		});
	}

	void Raft::Impl::TimeOutActionAdapter() {
		identities_[currentIdentity_]->TimeOutFunc();
	}

	CppAppendEntriesResponse Raft::Impl::ProcsAppendEntriesAdapter(CppAppendEntriesRequest request) {
		return identities_[currentIdentity_]->ProcsAppendEntriesFunc(request);
	}

	CppRequestVoteResponse Raft::Impl::ProcsRequestVoteAdapter(CppRequestVoteRequest request) {
		return identities_[currentIdentity_]->ProcsRequestVoteFunc(request);
	}


};

namespace SJTU {

	Raft::Raft(const ServerInfo &info, std::map<std::string, std::string> &data) : pImpl(
			std::make_unique<Impl>(info, data)) {}

	Raft::~Raft() {}

	void Raft::Start() {
		pImpl->eventQueue_.Start();
		pImpl->applyQueue_.Start();
		pImpl->IdentityTransform(FollowerNo);
		pImpl->server_end_->Monitor();
	}

	void Raft::Stop() {
		pImpl->eventQueue_.Stop();
		pImpl->applyQueue_.Stop();
		pImpl->server_end_->Stop();
		pImpl->timer_.Stop();
	}

}
