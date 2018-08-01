#include "../../include/raft/raft.h"

namespace SJTU {

	Raft::Raft(const ServerInfo &info, std::map<std::string, std::string> &data) :
			server_end(info.get_local()), info(info), applyQueue(data, state) {
		/// identity
		std::function<void(int)> transformer = std::bind(&Raft::IdentityTransform, this, std::placeholders::_1);
		identities[FollowerNo] = std::make_unique<Follower>(state, timer, transformer, client_ends, info);
		identities[CandidateNo] = std::make_unique<Candidate>(state, timer, transformer, client_ends, info);
		identities[LeaderNo] = std::make_unique<Leader>(state, timer, transformer, client_ends, info);
		currentIdentity = DownNo;

		server_end.BindServiceFunc(
				[this](const PbRequestVoteRequest *request, PbRequestVoteResponse *response) -> void {
					printf("current Identity %d\n", currentIdentity);
					identities[currentIdentity]->ProcsRequestVoteFunc(request, response);
				},
				[this](const PbAppendEntriesRequest *request, PbAppendEntriesResponse *response) -> void {
					printf("current Identity %d\n", currentIdentity);
					identities[currentIdentity]->ProcsAppendEntriesFunc(request, response);
				});

		/// gRPC client_ends
		for (const ServerId &srv_id : info.get_srvList()) {
			if (srv_id == info.get_local()) continue;
			client_ends.push_back(std::make_unique<RaftPeerClientImpl>(srv_id));
		}

		/// timer
		timer.BindTimeOutAction(std::bind(&Raft::TimeOutActionAdapter, this));
		timer.BindPushEvent(std::bind(&EventQueue::addEvent, &eventQueue, std::placeholders::_1));

		state.Init();
	}

	void Raft::IdentityTransform(IdentityNo identityNo) {

		printf("enter identity transformer\n");
		/// Note this!!!
		if (currentIdentity == identityNo) {
			printf("reseting timer\n");
			/// leader不会reset
			timer.Stop();
			timer.SetTimeOut(rand() % info.get_electionTimeout() + info.get_electionTimeout());
			timer.Start(false);
			printf("timer reset\n");
			return;
		}

		IdentityNo identityNo_orig = identityNo;
		RaftDebugContext &debugContext = GetDebug();
//		debugContext.before_tranform(currentIdentity, identityNo);
		ctx.before_tranform(currentIdentity, identityNo);

		eventQueue.addEvent([this, identityNo]() mutable {
			printf("transform from %d to %d\n", currentIdentity, identityNo);

			if (currentIdentity == DownNo)
				server_end.Monitor();
			else
				identities[currentIdentity]->leave();

			currentIdentity = identityNo;

			if (currentIdentity == DownNo) {
				timer.Stop();
				server_end.Stop();
			} else
				identities[currentIdentity]->init();
			printf("After transform function is carried out. \n");
		});
//		debugContext.after_tranform(currentIdentity, identityNo);
		ctx.after_tranform(currentIdentity, identityNo_orig);

	}

	void Raft::TimeOutActionAdapter() {
		identities[currentIdentity]->TimeOutFunc();
	}
};