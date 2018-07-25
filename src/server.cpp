#include "../include/server.h"
#include "../include/raft/raft.h"

namespace SJTU {
	struct Server::Impl {
		// gRPC ClientEnd;
		// Raft raft;
	};

	Server::~Server() = default;
	void Server::StartUp() {
		// pImpl->raft.init();
		// pImpl->raft.Start();
	}

	void Server::ShutDown() {
		// pImpl->raft.Stop();
	}
};
