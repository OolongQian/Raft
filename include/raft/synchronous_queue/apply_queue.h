#ifndef RAFT_PROJ_APPLY_QUEUE_H
#define RAFT_PROJ_APPLY_QUEUE_H

#include "../../log/entry.h"
#include "event_queue.h"

namespace SJTU {
	/**
	 * This class behaves like EventQueue, using an additional thread, executing committed log command tirelessly.
	 * The difference between this and EventQueue is that, EventQueue execute std::function<void()> while ApplyQueue
	 * execute std::function<void(Entry)>.
	 *
	 * Note that entry modifies map &data.
	 * */
	class ApplyQueue {
	public:
		explicit ApplyQueue(std::map<std::string, std::string> &data);

		~ApplyQueue();

		void Start();

		void Stop();

		void applyCommand(Entry entry);

	private:

		/// apply_queue_ is an EventQueue with a thread instance inside.
		/// this class is actually a function adapter.
		EventQueue apply_queue_;
		std::map<std::string, std::string> &data;
	};
};

#endif //RAFT_PROJ_APPLY_QUEUE_H
