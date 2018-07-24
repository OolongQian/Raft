#include "../../include/raft/timer/timer.h"
#include <boost/thread.hpp>
#include <functional>

namespace SJTU {
	struct Timer::Impl {
		int time_;   /// use boost::chrono lib later on.
		std::function<void()> timeOutAction_;
		std::function<void()> pushEvent_;
		boost::thread th;
	};

	void Timer::BindAction(std::function<void()> f) {
		pImpl->timeOutAction_ = std::move(f);
	}

	void Timer::Start() {
		pImpl->th = boost::thread([this] {
			// sleep(pImpl->time_);
			sleep(1);
			pImpl->timeOutAction_();
		});
	}

	void Timer::Stop() {
		pImpl->th.interrupt();
		if(pImpl->th.joinable())
			pImpl->th.join();
	}
};