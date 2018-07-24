#ifndef RAFT_PROJ_RAFT_H
#define RAFT_PROJ_RAFT_H

#include <memory>

namespace SJTU {
	class Raft {
		/**
		 * I haven't figured out what raft can do, so I just leave it here.
		 * */
	private:
		struct Impl;
		std::unique_ptr <Impl> pImpl;
	};
};

#endif //RAFT_PROJ_RAFT_H
