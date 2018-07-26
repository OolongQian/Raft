#ifndef RAFT_PROJ_STATE_H
#define RAFT_PROJ_STATE_H

#include "../log/log.h"

/**
 * State is a class of container that stores raft common information inside of it.
 * */
namespace SJTU {
	struct State {
		/// persistent state on all servers.
		int currentTerm;
		int votedFor;
		Log *logs;

		/// volatile state on all servers.
		int commitIndex;
		int lastApplied;

		/// volatile state on leaders.
		int *nextIndex;
		int *matchIndex;
	};
};

#endif //RAFT_PROJ_STATE_H
