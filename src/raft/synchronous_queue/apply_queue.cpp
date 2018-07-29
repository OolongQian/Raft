#include "../../../include/raft/synchronous_queue/apply_queue.h"

namespace SJTU {

	ApplyQueue::ApplyQueue(std::map<std::string, std::string> &data) : data(data) {}

	ApplyQueue::~ApplyQueue() {
		Stop();
	}

	void ApplyQueue::Start() {
		apply_queue_.Start();
	}

	void ApplyQueue::Stop() {
		apply_queue_.Stop();
	}

	void ApplyQueue::applyCommand(Entry entry) {
		if (entry.command == "Put") {
			apply_queue_.addEvent([&entry]() mutable {
				data[entry.key] = entry.val;
			});
		} else if (entry.command == "Get") {
			apply_queue_.addEvent([]() {
				fprintf(stderr, "Encounter Get command, what should I do?\n");
			});
		} else {
			fprintf(stderr, "unknown command!!! fail to apply\n");
		}
	}
};