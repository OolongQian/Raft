#ifndef RAFT_PROJ_LEADER_H
#define RAFT_PROJ_LEADER_H

#include "identity_base.h"

namespace SJTU {

/// implements identity_base abstract class.
class Leader : public IdentityBase {
public:

	explicit Leader(State &state, Timer &timer, std::function<void(int)> transformer,
									std::vector<std::unique_ptr<RaftPeerClientImpl> > &client_ends, boost::atomic<bool> &paused,
									const ServerInfo &info, ApplyQueue &apply_queue) :
			IdentityBase(state, timer, std::move(transformer), client_ends, paused, info, apply_queue) {}

	~Leader() override;

//	void ProcsAppendEntriesFunc(const PbAppendEntriesRequest *, PbAppendEntriesResponse *) override;

//	void ProcsRequestVoteFunc(const PbRequestVoteRequest *, PbRequestVoteResponse *) override;

//		CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest) override;

//		CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest) override;

	void init() override;

	void leave() override;

	void TimeOutFunc() override;

	/**
	 * Similar to Candidate::RequestVote().
	 * Contained by TimeOutFunc adapter.
	 *
	 * Problem is raised, because heartbeat is sent repeatedly, if the previous
	 * heartbeat is not responded while the next one is coming, what will happen?
	 *
	 * Heartbeat serves as appendEntries-RPCs simultaneously. If there are additional entries
	 * need to be applied, then it just append entry, otherwise it's empty heartbeat.
	 * */
	void SendHeartBeat();

	void CheckCommitIndexUpdate();

	/**
	 * There are two situations, one is leader receives request from a client,
	 * second is leader receives broadcast from a follower.
	 * In former case, leader has to create promise and future,
	 * in the second one otherwise.
	 *
	 * But in both case it has to carefully handle namespace and prmIndex.
	 * */
	void ProcsPutFunc(const PbPutRequest *, PbPutResponse *) override;

	/**
	 * Heartbeat serves as appendEntries-RPCs simultaneously. If there are additional entries
	 * need to be applied, then it just append entry, otherwise it's empty heartbeat.
	 * */

	size_t MakeHeartBeat(const ServerId &id, PbAppendEntriesRequest *request);

private:
	boost::mutex mtx_;

	void ProcsClientPutFunc(const PbPutRequest *request, PbPutResponse *response) override;

	void ProcsPeerPutFunc(const PbPutRequest *request, PbPutResponse *response) override;
};
};

#endif //RAFT_PROJ_LEADER_H
