#include "../../../include/raft/synchronous_queue/event_queue.h"


namespace SJTU {

	EventQueue::EventQueue() {
		while (!events_.empty()) events_.pop();
	}

	EventQueue::~EventQueue() = default;

	/**
	 * have to be synchronized by Impl.
	 * */
	void EventQueue::addEvent(std::function<void()> f) {
		boost::unique_lock<boost::mutex> lk(mtx_);
		events_.push(std::move(f));
		cond_.notify_all();
	}

	void EventQueue::Start() {
		printf("event queue thread is sent out...\n");
		th_ = boost::thread([this] {
			execute();
		});
	}

	void EventQueue::Stop() {
		th_.interrupt();
		if (th_.joinable())
			th_.join();
	}

	/**
		 * An internal member function that implements "Start()" interface.
		 *
		 * Because EventQueue is shared by multiple threads, when EventQueue
		 * itself in the phase of execution, other thread cannot interrupt it.
		 * On the other hand, when EventQueue detects that there's no event
		 * in the queue to be executed, it must leave the mutex and let other
		 * threads to add to it.
		 * */
	void EventQueue::execute() {
		while (true) {
			boost::unique_lock<boost::mutex> lk(mtx_);
			printf("synchronous_queue is waiting...\n");
			cond_.wait(lk, [this] { return !events_.empty(); });
			printf("synchronous_queue keeps going...\n");
			auto event = events_.front();
			events_.pop();
			lk.unlock();
			event();
		}
	}
};
