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
			eventQueue.Start();
			applyQueue.Start();
			server_end.PreMonitorInit();
			IdentityTransform(FollowerNo);
//			server_end.Monitor();		when get out of down, server_end starts to monitor.
		}

		void Stop() {
			eventQueue.Stop();
			applyQueue.Stop();
			server_end.Stop();
			timer.Stop();
		}

		static RaftDebugContext &GetDebug() {
			static RaftDebugContext debugContext;
			return debugContext;
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

		int currentIdentity;
		std::unique_ptr<IdentityBase> identities[IdentityNum];

		RaftServer server_end;
		std::vector<std::unique_ptr<RaftPeerClientImpl> > client_ends;

		boost::thread th;

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
