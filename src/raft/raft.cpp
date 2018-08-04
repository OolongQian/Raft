#include "../../include/raft/raft.h"

namespace SJTU {

	Raft::Raft(const ServerInfo &info, std::map<std::string, std::string> &data) :
			info(info),  applyQueue(data, state, info), server_end(info.get_local()) {
		/// identity
		std::function<void(int)> transformer = std::bind(&Raft::IdentityTransform, this, std::placeholders::_1);
		identities[FollowerNo] = std::make_unique<Follower>(state, timer, transformer, client_ends, info, applyQueue);
		identities[CandidateNo] = std::make_unique<Candidate>(state, timer, transformer, client_ends, info, applyQueue);
		identities[LeaderNo] = std::make_unique<Leader>(state, timer, transformer, client_ends, info, applyQueue);
		state.currentIdentity = DownNo;

		server_end.BindServiceFunc(
				[this](const PbRequestVoteRequest *request, PbRequestVoteResponse *response) -> void {
					printf("current Identity %d\n", state.currentIdentity);
					identities[state.currentIdentity]->ProcsRequestVoteFunc(request, response);
				},
				[this](const PbAppendEntriesRequest *request, PbAppendEntriesResponse *response) -> void {
					printf("current Identity %d\n", state.currentIdentity);
					identities[state.currentIdentity]->ProcsAppendEntriesFunc(request, response);
				},
				[this, id = info.get_local()](const PbPutRequest *request, PbPutResponse *response) -> void {
					printf("%s receive add log request\n", id.toString().c_str());
					identities[state.currentIdentity]->ProcsPutFunc(request, response);
				});

		/// gRPC client_ends
		for (const ServerId &srv_id : info.get_srvList()) {
//			if (srv_id == info.get_local()) continue;
			client_ends.push_back(std::make_unique<RaftPeerClientImpl>(srv_id));
		}

		/// timer
		timer.BindTimeOutAction(std::bind(&Raft::TimeOutActionAdapter, this));
		timer.BindPushEvent(std::bind(&EventQueue::addEvent, &eventQueue, std::placeholders::_1));

		state.Init();
	}

	void Raft::IdentityTransform(IdentityNo identityNo) {

		printf("enter test transformer\n");
		/// Note this!!!
		if (state.currentIdentity == identityNo) {
			printf("reseting timer\n");
			/// leader不会reset
			timer.Stop();
			timer.SetTimeOut(info.get_electionTimeout(), info.get_electionTimeout() * 2);
			timer.Start();
			printf("timer reset\n");
			return;
		}
#ifdef _UNIT_TEST
		IdentityNo identityNo_orig = identityNo;
		printf("%s transform from %d to %d\n", info.get_local().toString().c_str(), state.currentIdentity, identityNo);
		ctx.before_tranform(state.currentIdentity, identityNo);
#endif
		eventQueue.addEvent([this, identityNo]() mutable {
//			printf("transform from %d to %d\n", state.currentIdentity, identityNo);

			if (state.currentIdentity == DownNo)
				server_end.Monitor();
			else
				identities[state.currentIdentity]->leave();

			state.currentIdentity = identityNo;

			if (state.currentIdentity == DownNo) {
				timer.Stop();
				server_end.Stop();
			} else
				identities[state.currentIdentity]->init();
			printf("After transform function is carried out. \n");
			printf("have transformed to %d\n", state.currentIdentity);
		});
#ifdef _UNIT_TEST
		//		debugContext.after_tranform(state.currentIdentity, identityNo);
		ctx.after_tranform(state.currentIdentity, identityNo_orig);
#endif
		printf("3\n");
	}

	void Raft::TimeOutActionAdapter() {
		identities[state.currentIdentity]->TimeOutFunc();
	}
};