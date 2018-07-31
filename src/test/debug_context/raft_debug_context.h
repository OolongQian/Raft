#ifndef RAFT_PROJ_RAFT_DEBUG_CONTEXT_H
#define RAFT_PROJ_RAFT_DEBUG_CONTEXT_H

#include <functional>
#include "../../../include/common.h"

namespace SJTU {
	class RaftDebugContext {
	public:
		RaftDebugContext() {
			before_tranform = [](IdentityNo a, IdentityNo b) { fprintf(stderr, "before transform is empty\n"); };
			cnt = 0;
		}

		std::function<void(IdentityNo, IdentityNo)> before_tranform;

		boost::atomic<std::size_t> cnt{0};
	};
};

#endif //RAFT_PROJ_RAFT_DEBUG_CONTEXT_H
