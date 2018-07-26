#include "server_info.h"
#include "server.h"
#include "raft/raft.h"

namespace SJTU {
	struct Server::Impl {
		explicit Impl(const std::string &filename) : raft(info) {
			info.load(filename);
		}
//		 gRPC ClientEnd;
		Raft raft;
		ServerInfo info;
	};

	Server::Server(const std::string &filename) : pImpl(std::make_unique<Impl>(filename)) {}

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
