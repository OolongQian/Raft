#include "../../../include/raft/timer/timer.h"

namespace SJTU {
Timer::Timer() : low_time(100), high_time(100) {}

	Timer::~Timer() = default;

	void Timer::BindTimeOutAction(std::function<void()> f) {
		timeOutAction_ = std::move(f);
	}

	void Timer::BindPushEvent(std::function<void(std::function<void()>)> f) {
		pushEvent_ = std::move(f);
	}

void Timer::Start() {
	th = boost::thread([this] {
		try {
			int rand_time = rand() % (high_time - low_time + 1) + low_time;
			printf("timer sleep for %d milliseconds\n", rand_time);
			boost::this_thread::sleep_for(boost::chrono::milliseconds(rand_time));
			printf("%d ms has passed! timer is pushing event...\n", rand_time);
			pushEvent_(timeOutAction_);
		}
		catch (boost::thread_interrupted &) {
			printf("timer's sleep is interrupted... returning\n");
			return;
		}
		});
	}

	void Timer::Stop() {
		th.interrupt();
		th.join();
	}

void Timer::SetTimeOut(int low, int high) {
	low_time = low;
	high_time = high;
	}

	void Timer::Reset() {
		Stop();
		Start();
	}
};