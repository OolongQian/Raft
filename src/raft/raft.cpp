#include "../../include/raft/raft.h"
#include "../../include/raft/event_queue/event_queue.h"
#include "../../include/raft/timer/timer.h"

#include <iostream>

namespace SJTU {
	struct Raft::Impl {
		EventQueue eventQueue_;
		Timer timer_;
	};

	Raft::~Raft() = default;

	void Raft::init() {
		pImpl->timer_.BindAction([] {
			std::cout << "timer's terminate action is triggered" << std::endl;
		});
		pImpl->timer_.BindPushEvent(std::bind(&EventQueue::addEvent, &pImpl->eventQueue_, std::placeholders::_1));
	}

	void Raft::Start() {
		pImpl->eventQueue_.Start();
		pImpl->timer_.Start();
	}

	void Raft::Stop() {
		pImpl->eventQueue_.Stop();
		pImpl->timer_.Stop();
	}
};
