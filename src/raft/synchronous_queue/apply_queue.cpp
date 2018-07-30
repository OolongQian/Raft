#include "../../../include/raft/synchronous_queue/apply_queue.h"

namespace SJTU {

	ApplyQueue::ApplyQueue(std::map<std::string, std::string> &data, State &state) : data(data), state(state) {}

	ApplyQueue::~ApplyQueue() {
		Stop();
	}

	void ApplyQueue::Start() {
		th = boost::thread([this]() -> void {
			while (true) {
				boost::unique_lock<boost::mutex> lk(mtx);
				try {
					cond.wait(lk, [this]() { return state.commitIndex > state.lastApplied; });
				}
				catch (boost::thread_interrupted &) {
					return;
				}
				++state.lastApplied;
				applyCommand(state.log.at(state.lastApplied));
			}
		});
	}

	void ApplyQueue::Stop() {
		th.interrupt();
		th.join();
	}

	void ApplyQueue::applyCommand(Entry entry) {
		if (entry.command == "Put") {
			data[entry.key] = entry.val;
		} else if (entry.command == "Get") {
			fprintf(stderr, "I don't know who to apply Get\n");
		} else {
			fprintf(stderr, "Unknown command in applyQueue\n");
		}
	}

	void ApplyQueue::notify() {
		cond.notify_one();
	}
};