#include "../include/raft/raft.h"
#include "../include/server_info.h"
#include "../include/server.h"

namespace SJTU {
	struct Server::Impl {
		explicit Impl(const std::string &filename) { // : raft(info) {
#ifndef _NOLOG
			printf("Construct Server::Impl...\n");
			printf("Loading .json file...\n");
#endif
#ifndef _NOLOG
			info.load(filename);
			printf("Successfully loading. Display: \n");
			printf("local: %s\n", info.get_local().toString().c_str());
			printf("all Servers: ");
			for (const auto &remote : info.get_srvList()) {
				printf("%s; ", remote.toString().c_str());
			}
			printf("\n");

			printf("Use configured info to initialize raft...\n");
#endif
			pRaft = std::make_unique<Raft>(info);
		}

		std::unique_ptr<Raft> pRaft;
		ServerInfo info;
	};

	Server::Server(const std::string &filename) : pImpl(std::make_unique<Impl>(filename)) {
#ifndef _NOLOG
		printf("Construct Server...\n");
#endif
	}

	Server::~Server() = default;

	void Server::StartUp() {
		printf("server is starting up...\n");
		pImpl->pRaft->init();
		pImpl->pRaft->Start();
	}

	void Server::ShutDown() {
		printf("server is shuting down...\n");
		pImpl->pRaft->Stop();
	}
};
