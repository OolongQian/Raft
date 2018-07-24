#include "../../include/raft/raft.h"
#include "../../include/raft/event_queue.h"
#include "../../include/time/timer.h"

namespace SJTU {
	struct Raft::Impl {
		EventQueue eventQueue_;
		Timer timer_;
	};
};
