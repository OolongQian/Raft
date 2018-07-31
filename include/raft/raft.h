#ifndef RAFT_PROJ_RAFT_H
#define RAFT_PROJ_RAFT_H

#include <memory>
#include "../server_info.h"
#include "identities/follower.h"
#include "identities/candidate.h"
#include "identities/leader.h"
#include "identities/identity_base.h"
#include "../../src/test/debug_context/raft_debug_context.h"

namespace SJTU {
	class Raft {
	public:
		explicit Raft(const ServerInfo &info, std::map<std::string, std::string> &data);

		~Raft();

		void Start();

		void Stop();

		static RaftDebugContext &GetDebug() {
			static RaftDebugContext debugContext;
			return debugContext;
		}
	private:

		struct Impl;
		std::unique_ptr<Impl> pImpl;
	};
};

#endif //RAFT_PROJ_RAFT_H
