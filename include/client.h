#ifndef RAFT_PROJ_CLIENT_H
#define RAFT_PROJ_CLIENT_H

#include <string>
#include "raft/raft_proto/raft_client.h"

namespace SJTU {
class Client {
public:
	Client() = default;

	void Config(std::string filename);

	std::string Put(std::string key, std::string val, int deadline_ms);

	std::string Get(std::string key, int deadline_ms);

private:
	std::unique_ptr<RaftPeerClientImpl> pClient;
};
};
#endif //RAFT_PROJ_CLIENT_H
