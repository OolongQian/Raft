#include "../include/raft/raft.h"
#include "../include/server_info.h"
#include "../include/server.h"

namespace SJTU {
	struct Server::Impl {
		explicit Impl(const std::string &filename);

		void InitData();  /// init state machine inner data. (trivially by now)

		std::unique_ptr<Raft> pRaft;
		ServerInfo info;
		std::map<std::string, std::string> data;  /// data to be coherent.
	};

	Server::Impl::Impl(const std::string &filename) { // : raft(info) {
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

	void Server::Impl::InitData() {
		data.clear();
	}
};

namespace SJTU {
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
