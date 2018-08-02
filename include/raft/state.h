#ifndef RAFT_PROJ_STATE_H
#define RAFT_PROJ_STATE_H

#include <vector>
#include <iostream>
#include <map>
#include <boost/thread/mutex.hpp>
#include "../server_info.h"
#include "../log/log_array.h"

/**
 * State is a class of container that stores raft common information inside of it.
 * */
namespace SJTU {
	struct State {
		/// persistent state on all servers.
		long long currentTerm;
		ServerId votedFor;
		LogArray log;

		/// volatile state on all servers.
		long long commitIndex;
		long long lastApplied;

		/// volatile state on leaders.
		std::map<ServerId, long long> nextIndex;
		std::map<ServerId, long long> matchIndex;

		/// find whether one entry exists in current log.
//		bool IfLogContains(const Log &entry);
		/// the initialization of state consists of init persistent states and volatile states.
		State() = default;

		void Init();

		/// in order to let the first log index be 1, push a trivial log in the front.
		void Load();

		boost::mutex entries_mtx;
	};

};

#endif //RAFT_PROJ_STATE_H
