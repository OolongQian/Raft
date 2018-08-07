#ifndef RAFT_PROJ_RAFT_H
#define RAFT_PROJ_RAFT_H

#include <memory>
#include "../server_info.h"
#include "identities/follower.h"
#include "identities/candidate.h"
#include "identities/leader.h"
#include "identities/identity_base.h"
#include "../../src/test/debug_context/raft_debug_context.h"
#include "../my_server.h"
#include "raft_proto/raft_server.h"
#include "../../include/raft/synchronous_queue/event_queue.h"
#include "synchronous_queue/apply_queue.h"

#include "../debug_header.h"

namespace SJTU {
class Raft {
public:
	explicit Raft(const ServerInfo &info, std::map<std::string, std::string> &data);

	~Raft() {}

	void Start() {
		std::string filename = (info.get_local().toString() + "_persistent");
		state.Load(filename);

		eventQueue.Start();
		applyQueue.Start();
		server_end.Monitor();
		IdentityTransform(FollowerNo);
	}

	void Pause() {
		eventQueue.Stop();
		applyQueue.Stop();
		server_end.Pause();
		timer.Stop();
		state.currentIdentity = FollowerNo;    /// if change to be DownNo, it will invoke undesirable function.
	}

	void Resume() {
		eventQueue.Start();
		applyQueue.Start();
		server_end.Resume();
		IdentityTransform(FollowerNo);
	}

	void Stop() {
		eventQueue.Stop();
		applyQueue.Stop();
		server_end.Stop();
		timer.Stop();
		std::string filename = (info.get_local().toString() + "_persistent");
		state.Store(filename);
	}

private:
#ifdef _UNIT_TEST
public:
#endif
	State state;
	const ServerInfo &info;

	Timer timer;
	EventQueue eventQueue;
	ApplyQueue applyQueue;

	std::unique_ptr<IdentityBase> identities[IdentityNum];

	RaftServer server_end;
	std::vector<std::unique_ptr<RaftPeerClientImpl> > client_ends;

#ifdef _UNIT_TEST
	RaftDebugContext ctx;
#endif

private:
	/**
	 * This function simply invokes identity classes' leave and init function.
	 * But during identity transformation, server state changes (pass by reference).
	 * timer is reset (pass by reference. rpc is set out.
	 * Many heavy work is done, I wanna distribute these works to specialized classes,
	 * thus leaving detailed implementation inside identities.
	 * */
	void IdentityTransform(IdentityNo);

	void TimeOutActionAdapter();
};
};

#endif //RAFT_PROJ_RAFT_H
