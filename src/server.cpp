#include "server.h"
#include "raft/raft.h"

namespace SJTU {
	struct Server::Impl {
//		 gRPC ClientEnd;
		Raft raft;
	};

	Server::Server() : pImpl(std::make_unique<Impl>()) {}

	Server::~Server() = default;

	void Server::StartUp() {
		printf("server is starting up...\n");
		pImpl->raft.init();
		pImpl->raft.Start();
	}

	void Server::ShutDown() {
		printf("server is shuting down...\n");
		pImpl->raft.Stop();
	}
};
