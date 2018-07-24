#include "../../include/raft/event_queue.h"

#include <queue>
#include <functional>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

namespace SJTU {
	struct EventQueue::Impl {
		std::queue<std::function<void()> > events_;

		/**
		 * all boost::variables for synchronization are here, good!
		 * */
		boost::mutex mtx_;
		boost::condition_variable cond_;


		/**
		 * An internal member function that implements "Start()" interface.
		 *
		 * Because EventQueue is shared by multiple threads, when EventQueue
		 * itself in the phase of execution, other thread cannot interrupt it.
		 * On the other hand, when EventQueue detects that there's no event
		 * in the queue to be executed, it must leave the mutex and let other
		 * threads to add to it.
		 * */
		void execute() {
			while(true) {
				boost::unique_lock<boost::mutex> lk(mtx_);
				/// only when events_ are present can execute forward...
				cond_.wait(lk, [this] { return !events_.empty(); });
				auto event = events_.front(); events_.pop();
				event();
			}
		}

		void addEvent(std::function<void()> f) {
			boost::unique_lock<boost::mutex> lk(mtx_);
			cond_.wait(lk, [this] { return events_.empty(); });
			events_.push(std::move(f));
		}
	};

	/**
	 * have to be synchronized by Impl.
	 * */
	void EventQueue::addEvent(std::function<void()> f) {
		pImpl->addEvent(std::move(f));
	}
};
