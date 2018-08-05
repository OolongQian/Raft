#ifndef RAFT_PROJ_APPLY_QUEUE_H
#define RAFT_PROJ_APPLY_QUEUE_H

#include <boost/thread/mutex.hpp>
#include <boost/thread.hpp>
#include "../../log/log_array.h"
#include "event_queue.h"
#include "../state.h"

namespace SJTU {
/**
 * "If commitIndex > lastApplied: increment lastApplied, apply log[lastApplied] to state machine".
 *
 * ApplyQueue has access to state_, and log. Meanwhile, in order to apply command, it needs to modify KV pairs.
 * this is a automated process where applyIndex is changed, this may result in Asynchronous disaster.
 *
 * ApplyQueue is the only means to increase lastApplied.
 * */
class ApplyQueue {
public:
	explicit ApplyQueue(std::map<std::string, std::string> &data, State &state, const ServerInfo &info);

	~ApplyQueue();

	void Start();

	void Stop();

	/**
	 * This is used when commitIndex is updated, notify the thread inside carry on.
	 *
	 * Because commitIndex won't be added by several threads, it needn't synchronize.
	 * */
	void notify();

private:
	State &state;
	std::map<std::string, std::string> &data;
	const ServerInfo &info;

	boost::mutex mtx;
	boost::thread th;
	boost::condition_variable cond;

private:
	void applyCommand(Entry entry);
};
};  // namespace

#endif //RAFT_PROJ_APPLY_QUEUE_H
