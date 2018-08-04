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
	printf("server is shuting down...current Identity is %d\n", pRaft->state.currentIdentity);
	pRaft->Stop();
}

void Server::InitData() {
	data.clear();
}

const ServerInfo &Server::GetInfo() {
	return info;
}
};
