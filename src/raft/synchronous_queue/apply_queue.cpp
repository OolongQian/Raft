#include "../../../include/raft/synchronous_queue/apply_queue.h"

namespace SJTU {

ApplyQueue::ApplyQueue(std::map<std::string, std::string> &data, State &state, const ServerInfo &info) :
		state(state), data(data), info(info) {}

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
			/// state.lastApplied is only updated by applyQueue, need no lock.
			++state.lastApplied;
//			printf("server id: %s, apply index %lld, senderId %s, entryPrmIndex %lld\n", info.get_local().toString().c_str(), state.lastApplied,
//						 state.log.at(state.lastApplied).replyerId.c_str(), state.log.at(state.lastApplied).prmIndex);
			applyCommand(state.log.at(state.lastApplied));
		}
	});
}

void ApplyQueue::Stop() {
	th.interrupt();
	th.join();
}

void ApplyQueue::applyCommand(Entry entry) {
	char msg[100];
	if (entry.command == "Put") {
		data[entry.key] = entry.val;
		sprintf(msg, "Client has associated key %s with value %s", entry.key.c_str(), entry.val.c_str());
	} else if (entry.command == "Get") {
		fprintf(stderr, "I don't know who to apply Get\n");
		sprintf(msg, "Client has got value %s from key %s", entry.val.c_str(), entry.key.c_str());
	} else {
		fprintf(stderr, "Unknown command in applyQueue\n");
		sprintf(msg, "Unknown command");
	}

//	if (info.get_local().toString() == "127.0.0.1:50000") {
//		printf("localId %s, replyerId: %s, key %s, val %s\n", info.get_local().toString().c_str(),
//					 entry.replyerId.c_str(), entry.key.c_str(), entry.val.c_str());
//	}

	if (entry.replyerId == info.get_local().toString()) {
		/// it is me that is to reply.
		boost::shared_lock<boost::shared_mutex> lk(state.prmRepoMtx);
//		printf("serverId %s, entryPrmIndex %lld\n", info.get_local().toString().c_str(), entry.prmIndex);
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
