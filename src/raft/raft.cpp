#include "raft/raft.h"
#include "raft/event_queue/event_queue.h"
#include "raft/timer/timer.h"
#include "raft/state.h"
#include "raft/raft_proto/raft_peer_server.h"
#include "raft/raft_proto/raft_peer_client.h"

#include <iostream>

namespace SJTU {
	struct Raft::Impl {
		EventQueue eventQueue_;
		Timer timer_;
		State state_;
		RaftPeerServerImpl server_end_;
		RaftPeerClient client_end_;
	};

	Raft::Raft() : pImpl(std::make_unique<Impl>()) {}

	Raft::~Raft() = default;

	void Raft::init() {
		printf("raft is initting...\n");
		printf("raft is binding terminate action...\n");

		pImpl->timer_.BindPushEvent(std::bind(&EventQueue::addEvent, &pImpl->eventQueue_, std::placeholders::_1));
		pImpl->timer_.BindTimeOutAction([] {
			std::cout << "timer's terminate action is triggered" << std::endl;
		});

//		pImpl->timer_.BindTimeOutAction(std::bind(&EventQueue::addEvent, &pImpl->eventQueue_, [] {
//			std::cout << "timer's terminate action is triggered" << std::endl;
//		}));
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
