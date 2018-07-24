#include "../include/server.h"

namespace SJTU {
	struct Server::Impl {
		gRPC ClientEnd;
		raft::Raft raft;
	};

	void Server::Start() {}

	void Server::ShutDown() {}
};
