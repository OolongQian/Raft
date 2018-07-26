#ifndef RAFT_PROJ_RAFT_H
#define RAFT_PROJ_RAFT_H

#include <memory>
#include <server_info.h>

namespace SJTU {
	class Raft {
	public:
		explicit Raft(const ServerInfo &info);

		~Raft();
		/**
		 * I haven't figured out what raft can do, so I just leave it here.
		 * */

		/**
		 * bind terminate action for timer and start eventQueue and Timer.
		 * */
		void init();

		void Start();

		void Stop();

	private:
		struct Impl;
		std::unique_ptr<Impl> pImpl;
	};
};

#endif //RAFT_PROJ_RAFT_H
