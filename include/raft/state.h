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

		/// find whether one entry exists in current log.
//		bool IfLogContains(const Log &entry);
	};
};

#endif //RAFT_PROJ_STATE_H
