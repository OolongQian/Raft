#include "../../include/time/timer.h"
#include <boost/thread.hpp>
#include <functional>

namespace SJTU {
	struct Timer::Impl {
		int time_;   /// use boost::chrono lib later on.
		std::function<void()> timeOutAction_;
		boost::thread th;

	};

	void Timer::BindAction(std::function<void()> f) {
		pImpl->timeOutAction_ = std::move(f);
	}

	void Timer::Start() {
		pImpl->th = boost::thread([this] {
			sleep(pImpl->time_);
			pImpl->timeOutAction_();
		});
	}
};