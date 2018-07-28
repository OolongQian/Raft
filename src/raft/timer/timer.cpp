#include "../../../include/raft/timer/timer.h"
#include <boost/thread.hpp>
#include <functional>
#include <thread>

namespace SJTU {
	struct Timer::Impl {
		int time_;   /// use boost::chrono lib later on.
		std::function<void()> timeOutAction_;
		std::function<void(std::function<void()>)> pushEvent_;
		boost::thread th;

		Impl() : time_(rand() % 150 + 150) {}
	};

	Timer::Timer() : pImpl(std::make_unique<Impl>()) {}

	Timer::~Timer() = default;

	void Timer::BindTimeOutAction(std::function<void()> f) {
		pImpl->timeOutAction_ = std::move(f);
	}

	void Timer::BindPushEvent(std::function<void(std::function<void()>)> f) {
		pImpl->pushEvent_ = std::move(f);
	}

	void Timer::Start() {
		pImpl->th = boost::thread([this] {
			// sleep(pImpl->time_);
//			std::this_thread::sleep_for(std::chrono::duration_cast())
			try {
				std::this_thread::sleep_for(std::chrono::milliseconds(pImpl->time_));
				printf("%d ms has passed! timer is pushing event...\n", pImpl->time_);
				pImpl->pushEvent_(pImpl->timeOutAction_);
			}
			catch (boost::thread_interrupted &) {
				printf("timer's sleep is interrupted... returning\n");
				return;
			}

//			pImpl->timeOutAction_();
//			pImpl->pushEvent_(pImpl->timeOutAction_);
//			 pImpl->timeOutAction_();
			// pImpl->pushEvent_([] { printf("push event...\n"); });
		});
	}

	void Timer::Stop() {
		pImpl->th.interrupt();
		pImpl->th.join();
	}

	void Timer::SetTimeOut(int time_limit) {
		pImpl->time_ = time_limit;
	}
};