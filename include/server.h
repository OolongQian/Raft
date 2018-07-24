#ifndef RAFT_PROJ_SERVER_H
#define RAFT_PROJ_SERVER_H

#include <memory>

namespace SJTU {
	class Server {
	public:
		void StartUp();
		void ShutDown();

	private:
		struct Impl;
		std::unique_ptr<Impl> pImpl;
	};
};

#endif //RAFT_PROJ_SERVER_H
