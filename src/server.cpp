
#include "../include/server.h"

namespace SJTU {
	Server::Server(const std::string &filename) {
		info.load(filename);
	}

	Server::~Server() = default;

	void Server::Init() {
		InitData();
		pRaft = std::make_unique<Raft>(info, data);
	}

	void Server::StartUp() {
		if (pRaft == nullptr) {
			std::cerr << "pImpl hasn't been initialized" << std::endl;
			return;
		}
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
