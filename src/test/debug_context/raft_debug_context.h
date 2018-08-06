#ifndef RAFT_PROJ_RAFT_DEBUG_CONTEXT_H
#define RAFT_PROJ_RAFT_DEBUG_CONTEXT_H

#include <functional>
#include <boost/atomic.hpp>
#include "../../../include/server_info.h"

namespace SJTU {
	class RaftDebugContext {
	public:
		RaftDebugContext() {
			before_tranform = [](IdentityNo a, IdentityNo b) { ; };
			after_tranform = [](IdentityNo a, IdentityNo b) { ; };
//			before_tranform = [](IdentityNo a, IdentityNo b) { fprintf(stderr, "before transform is empty\n"); };
//			after_tranform = [](IdentityNo a, IdentityNo b) { fprintf(stderr, "after transform is empty\n"); };
			cnt = 0;
		}

		std::function<void(IdentityNo, IdentityNo & )> before_tranform;

		std::function<void(IdentityNo, IdentityNo & )> after_tranform;

		boost::atomic<std::size_t> cnt{0};
	};
};

#endif //RAFT_PROJ_RAFT_DEBUG_CONTEXT_H
