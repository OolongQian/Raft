#include "../../include/raft/raft.h"

namespace SJTU {

	Raft::Raft(const ServerInfo &info, std::map<std::string, std::string> &data) :
			info(info),  applyQueue(data, state, info), server_end(info.get_local()) {
		/// identity
		std::function<void(int)> transformer = std::bind(&Raft::IdentityTransform, this, std::placeholders::_1);
		identities[FollowerNo] = std::make_unique<Follower>(state, timer, transformer, client_ends, server_end.paused, info,
																												applyQueue);
		identities[CandidateNo] = std::make_unique<Candidate>(state, timer, transformer, client_ends, server_end.paused,
																													info, applyQueue);
		identities[LeaderNo] = std::make_unique<Leader>(state, timer, transformer, client_ends, server_end.paused, info,
																										applyQueue);
		state.currentIdentity = DownNo;

		server_end.BindServiceFunc(
				[this](const PbRequestVoteRequest *request, PbRequestVoteResponse *response) -> void {
					identities[state.currentIdentity]->ProcsRequestVoteFunc(request, response);
				},
				[this](const PbAppendEntriesRequest *request, PbAppendEntriesResponse *response) -> void {
//					printf("%d\n", state.currentIdentity);
					identities[state.currentIdentity]->ProcsAppendEntriesFunc(request, response);
				},
				[this, id = info.get_local()](const PbClientRequest *request, PbClientResponse *response) -> void {
					identities[state.currentIdentity]->ProcsClientFunc(request, response);
				});

		/// gRPC client_ends
		for (const ServerId &srv_id : info.get_srvList()) {
//			if (srv_id == info.get_local()) continue;
			client_ends.push_back(std::make_unique<RaftPeerClientImpl>(srv_id));
		}

		/// timer
		timer.BindTimeOutAction(std::bind(&Raft::TimeOutActionAdapter, this));
		timer.BindPushEvent(std::bind(&EventQueue::addEvent, &eventQueue, std::placeholders::_1));
	}

	void Raft::IdentityTransform(IdentityNo identityNo) {

		/// Note this!!!
		if (state.currentIdentity == identityNo) {
			/// leader不会reset
//			fprintf(stderr, "timer reset for follower\n");
			timer.Stop();
			timer.SetTimeOut(info.get_electionTimeout(), info.get_electionTimeout() * 2);
			timer.Start();
			return;
		}
#ifdef _UNIT_TEST
		IdentityNo identityNo_orig = identityNo;
		ctx.before_tranform(state.currentIdentity, identityNo);
#endif
		eventQueue.addEvent([this, identityNo]() mutable {
			fprintf(stderr, "server: %s transform from %d to %d\n", info.get_local().toString().c_str(),
							state.currentIdentity, identityNo);


			if (state.currentIdentity != DownNo) {
				applyQueue.Stop();
				server_end.paused = true;
				identities[state.currentIdentity]->leave();
			}

			state.currentIdentity = identityNo;

			if (state.currentIdentity == DownNo) {
				Pause();
			} else {
				identities[state.currentIdentity]->init();
				applyQueue.Start();
				server_end.paused = false;
			}
		});
#ifdef _UNIT_TEST
		ctx.after_tranform(state.currentIdentity, identityNo_orig);
#endif
	}

	void Raft::TimeOutActionAdapter() {
		identities[state.currentIdentity]->TimeOutFunc();
	}
};