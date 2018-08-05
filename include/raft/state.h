#ifndef RAFT_PROJ_STATE_H
#define RAFT_PROJ_STATE_H

#include <vector>
#include <iostream>
#include <map>
#include <boost/thread/mutex.hpp>
#include <future>
#include "../server_info.h"
#include "../log/log_array.h"

/**
 * State is a class of container that stores raft common information inside of it.
 * */
namespace SJTU {

struct State {
	/// persistent state on all servers.
	int currentIdentity;
	long long currentTerm;
	ServerId votedFor;
	LogArray log;						/// log is already a synchronized class

	/// volatile state on all servers.
	long long commitIndex;
	long long lastApplied;

	/// volatile state on leaders.
	std::map<ServerId, long long> nextIndex;
	std::map<ServerId, long long> matchIndex;

	std::map<long long, std::promise<std::string> > prmRepo;
	int prmRepoIdx;

	/// find whether one entry exists in current log.
	/// the initialization of state consists of init persistent states and volatile states.
	State() : prmRepoIdx(0) {}

	void Load(std::string filename);

	void Store(std::string filename);

	boost::shared_mutex curIdentityMtx, curTermMtx, votedForMtx, cmtIdxMtx, lastAplMtx,
			nxtIdxMtx, mtchIdxMtx, prmRepoMtx, prmRepoIdxMtx, logMasterMtx;

};
};

#endif //RAFT_PROJ_STATE_H
