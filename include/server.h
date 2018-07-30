#ifndef RAFT_PROJ_SERVER_H
#define RAFT_PROJ_SERVER_H

#include <memory>
#include "../include/raft/raft.h"
#include "../include/server_info.h"

namespace SJTU {
	class Server {
	public:
		Server(const std::string &filename);

		~Server();

		void StartUp();

		void ShutDown();

	private:
		std::unique_ptr<Raft> pRaft;
		ServerInfo info;
		std::map<std::string, std::string> data;  /// data to be coherent.

	private:
		void InitData();    /// init state machine inner data. (trivially by now)
	};
};


#endif //RAFT_PROJ_SERVER_H
