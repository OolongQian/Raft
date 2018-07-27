#include "../../../include/raft/timer/timer.h"
#include <boost/thread.hpp>
#include <functional>

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

	void Timer::BindTimeAndAction(int time_limit, std::function<void()> f) {
		pImpl->time_ = time_limit;
		pImpl->timeOutAction_ = std::move(f);
	}

	void Timer::BindPushEvent(std::function<void(std::function<void()>)> f) {
		pImpl->pushEvent_ = std::move(f);
	}

	void Timer::Start() {
		pImpl->th = boost::thread([this] {
			// sleep(pImpl->time_);
			sleep(1);
			printf("timer is pushing event...\n");
			pImpl->pushEvent_(pImpl->timeOutAction_);
//			 pImpl->timeOutAction_();
			// pImpl->pushEvent_([] { printf("push event...\n"); });
		});
	}

	void Timer::Stop() {
		pImpl->th.interrupt();
		if (pImpl->th.joinable())
			pImpl->th.join();
	}

	void Timer::Pause() {

	}

	void Timer::Resume() {

	}
};