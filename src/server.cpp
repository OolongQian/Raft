#include <fstream>
#include "../include/server.h"

namespace SJTU {
Server::Server(const std::string &filename) {
	info.load(filename);
}

Server::~Server() = default;

void Server::Init() {
	std::string filename = (info.get_local().toString() + "_KV");
	LoadData(filename);
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
	pRaft->Stop();
	std::string filename = (info.get_local().toString() + "_KV");
	StoreData(filename);
}

const ServerInfo &Server::GetInfo() {
	return info;
}

void Server::LoadData(std::string filename) {
	std::ifstream fin(filename, std::ios::in);
	if (fin.is_open()) {
		std::string key, val;

		size_t map_size;
		fin >> map_size;
		for (size_t i = 0; i < map_size; ++i) {
			fin >> key >> val;
			data.insert(std::pair<std::string, std::string>(key, val));
		}
		fin.close();
	} else {
		data.clear();
	}
}

void Server::StoreData(std::string filename) {
	std::ofstream fout(filename, std::ios::out);
	fout << data.size() << std::endl;
	for (const auto &elem : data) {
		fout << elem.first << ' ' << elem.second << std::endl;
	}
	fout.close();
}

void Server::Resume() {
	fprintf(stderr, "server %s is resuming\n", info.get_local().toString().c_str());
	pRaft->Resume();
}

void Server::Pause() {
	fprintf(stderr, "server %s is pausing\n", info.get_local().toString().c_str());
	pRaft->Pause();
}
};
