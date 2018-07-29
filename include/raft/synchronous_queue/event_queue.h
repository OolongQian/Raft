#ifndef RAFT_PROJ_EVENT_QUEUE_H
#define RAFT_PROJ_EVENT_QUEUE_H

#include <functional>
#include <memory>

namespace SJTU {
	class EventQueue {
	public:
		EventQueue();

		~EventQueue();

		/**
		 * This Start() member function triggers EventQueue's execution,
		 * which turns EventQueue into a consumer, executing or waiting for
		 * operations inside the EventQueue.
		 *
		 * This is essentially a "model of producer and consumer".
		 * */
		void Start();

		void Stop();

		/**
		 * A member function which is meant to be bound into other thread, allowing
		 * them to add events to this EventQueue externally. Which eventually makes up
		 * of an event-driven program.
		 * */
		void addEvent(std::function<void()> f);

	private:
		struct Impl;
		std::unique_ptr<Impl> pImpl;
	};
};

#endif //RAFT_PROJ_EVENT_QUEUE_H
