#include "../../../include/raft/timer/timer.h"

namespace SJTU {
	Timer::Timer() : time_(rand() % 150 + 150) {}

	Timer::~Timer() = default;

	void Timer::BindTimeOutAction(std::function<void()> f) {
		timeOutAction_ = std::move(f);
	}

	void Timer::BindPushEvent(std::function<void(std::function<void()>)> f) {
		pushEvent_ = std::move(f);
	}

	void Timer::Start(const bool repeat) {
		th = boost::thread([this, repeat] {
			// sleep(time_);
//			std::this_thread::sleep_for(std::chrono::duration_cast())
			if (repeat) {
				printf("timer operates a repetitive work\n");
				while (true) {
					try {
						boost::this_thread::interruption_point();
						boost::this_thread::sleep_for(boost::chrono::milliseconds(time_));
						boost::this_thread::interruption_point();
						printf("%d ms has passed! timer is pushing event...\n", time_);
						pushEvent_(timeOutAction_);
					}
					catch (boost::thread_interrupted &) {
						printf("timer's sleep is interrupted... returning\n");
						return;
					}
				}
			} else {
				try {
					boost::this_thread::interruption_point();
					boost::this_thread::sleep_for(boost::chrono::milliseconds(time_));
					boost::this_thread::interruption_point();
					printf("%d ms has passed! timer is pushing event...\n", time_);
					pushEvent_(timeOutAction_);
				}
				catch (boost::thread_interrupted &) {
					printf("timer's sleep is interrupted... returning\n");
					return;
				}
			}


//			timeOutAction_();
//			pushEvent_(timeOutAction_);
//			 timeOutAction_();
			// pushEvent_([] { printf("push event...\n"); });
		});
	}

	void Timer::Stop() {
		th.interrupt();
		th.join();
	}

	void Timer::SetTimeOut(int time_limit) {
		time_ = time_limit;
	}

	void Timer::Reset() {
		Stop();
		Start(false);
	}
};