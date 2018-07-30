
#include "../include/server.h"

namespace SJTU {
	Server::Server(const std::string &filename) {
#ifndef _NOLOG
		printf("Construct Server...\n");
#endif

#ifndef _NOLOG
		printf("Construct Server::Impl...\n");
		printf("Loading .json file...\n");
#endif
#ifndef _NOLOG
		info.load(filename);
		InitData();
		printf("Successfully loading. Display: \n");
		printf("local: %s\n", info.get_local().toString().c_str());
		printf("all Servers: ");
		for (const auto &remote : info.get_srvList()) {
			printf("%s; ", remote.toString().c_str());
		}
		printf("\n");

		printf("Use configured info to initialize raft...\n");
#endif
		pRaft = std::make_unique<Raft>(info, data);
	}

	Server::~Server() = default;

	void Server::StartUp() {
		printf("server is starting up...\n");
		pRaft->init();
		pRaft->Start();
	}

	void Server::ShutDown() {
		printf("server is shuting down...\n");
		pRaft->Stop();
	}

	void Server::InitData() {
		data.clear();
	}
};
