#ifndef RAFT_PROJ_EVENT_QUEUE_H
#define RAFT_PROJ_EVENT_QUEUE_H

#include <functional>
#include <memory>
#include <queue>
#include <functional>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>


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

		void execute();
	private:
		/**
		 * all boost::variables for synchronization are here, good!
		 * */
		std::queue<std::function<void()> > events_;
		boost::mutex mtx_;
		boost::condition_variable cond_;
		boost::thread th_;
	};
};

#endif //RAFT_PROJ_EVENT_QUEUE_H
