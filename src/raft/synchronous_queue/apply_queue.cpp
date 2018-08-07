#include "../../../include/raft/synchronous_queue/apply_queue.h"

namespace SJTU {

ApplyQueue::ApplyQueue(std::map<std::string, std::string> &data, State &state, const ServerInfo &info) :
		state(state), data(data), info(info) {}

ApplyQueue::~ApplyQueue() {
	Stop();
}

void ApplyQueue::Start() {
	if(th.joinable()) return;
	th = boost::thread([this]() -> void {
		while (true) {
			boost::unique_lock<boost::mutex> lk(mtx);
			try {
				cond.wait(lk, [this]() { return state.commitIndex > state.lastApplied; });
			}
			catch (boost::thread_interrupted &) {
				lk.unlock();
				return;
			}
			/// state.lastApplied is only updated by applyQueue, need no lock.
			++state.lastApplied;
			applyCommand(state.log.at(state.lastApplied));
		}
	});
}

void ApplyQueue::Stop() {
	if (!th.joinable())
		return;
	th.interrupt();
	th.join();
}

void ApplyQueue::applyCommand(Entry entry) {
	char msg[100];
	if (entry.command == "Put") {
		data[entry.key] = entry.val;
		sprintf(msg, "Client has associated key %s with value %s", entry.key.c_str(), entry.val.c_str());
	} else if (entry.command == "Get") {
//		fprintf(stderr, "I don't know who to apply Get\n");
		sprintf(msg, "Client has got value %s from key %s", entry.val.c_str(), entry.key.c_str());
	} else {
		fprintf(stderr, "Unknown command in applyQueue\n");
		sprintf(msg, "Unknown command");
	}

	if (entry.replyerId == info.get_local().toString()) {
		/// it is me that is to reply.
		boost::shared_lock<boost::shared_mutex> lk(state.prmRepoMtx);
		state.prmRepo.at(entry.prmIndex).set_value(std::string(msg));
	} else {
		/// I'm not the one responsible for replying.
//		printf("applyCommand %s\n", msg);
	}
}

void ApplyQueue::notify() {
	cond.notify_one();
}
};
