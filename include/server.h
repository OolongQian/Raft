#ifndef RAFT_PROJ_SERVER_H
#define RAFT_PROJ_SERVER_H

#include <memory>
#include "../include/raft/raft.h"
#include "../include/server_info.h"

#include "debug_header.h"

namespace SJTU {
class Server {
public:
	Server(const std::string &filename);

	~Server();

	void Init();

	void StartUp();

	void Pause();

	void Resume();

	void ShutDown();

	const ServerInfo &GetInfo();

#ifdef _UNIT_TEST

	const long long GetCurrentTerm() {
		return pRaft->state.currentTerm;
	}

	const IdentityNo GetIdentity() {
		return pRaft->state.currentIdentity;
	}

	RaftDebugContext &GetCtx() {
		return pRaft->ctx;
	}

	const ServerId GetServerId() {
		return pRaft->info.get_local();
	}

	const std::map<std::string, std::string> &GetKV() {
		return data;
	}

	State &GetState() {
		return pRaft->state;
	}

#endif

private:
	std::unique_ptr<Raft> pRaft;
	ServerInfo info;
	std::map<std::string, std::string> data;  /// data to be coherent.

private:
	void LoadData(std::string filename);    /// init state machine inner data. (trivially by now)
	void StoreData(std::string filename);
};
};


#endif //RAFT_PROJ_SERVER_H
