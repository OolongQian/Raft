#include "../../../include/raft/identities/identity_base.h"
#include <boost/timer.hpp>

#define _NOT_TRIVIAL_VOTE
#define _NOT_TRIVIAL_APPEND

namespace SJTU {

void
SJTU::IdentityBase::ProcsAppendEntriesFunc(const PbAppendEntriesRequest *request, PbAppendEntriesResponse *response) {
	boost::timer t;
	while (paused) {
		if (t.elapsed() * 1000 > PEER_TIMEOUT_MILLISECOND)
			return;
		std::this_thread::yield();
	}
//	printf("%lf\n", t.elapsed());

//	fprintf(stderr, "serverId %s is processing appendEntries RPC, Identity %d\n", info.get_local().toString().c_str(),
//					state_.currentIdentity);

	response->set_inconsist(false);

	boost::shared_lock<boost::shared_mutex> lk1(state_.curTermMtx, boost::defer_lock);
	boost::unique_lock<boost::shared_mutex> lk2(state_.votedForMtx, boost::defer_lock);
	boost::lock(lk1, lk2);

	if (request->term() > state_.currentTerm) {
		state_.votedFor.clear();
	}

	/**
	 * Default implementation.
	 * */
	response->set_term(state_.currentTerm);
	response->set_success(true);

#ifdef _NOT_TRIVIAL_APPEND
	/// reply false if request is out of date.
	if (request->term() < state_.currentTerm)
		response->set_success(false);
	/// reply false if log doesn't contain an entry at prevLogIndex whose term matches prevLogTerm.

	lk1.unlock();
	lk2.unlock();

	boost::unique_lock<boost::shared_mutex> logMasterLk(state_.logMasterMtx);

	if (!state_.log.has(request->prevlogindex()) ||
			state_.log.at(request->prevlogindex()).term != request->prevlogterm()) {
		response->set_inconsist(true);
		response->set_success(false);
		return;
	}

	/// if an existing entry conflicts with a new one (same index but different terms), delete the existing entry and all that follow it.
	/// append any new entries not already in the log.
	/// note that entryIndex should be monotonically increasing.
	for (int i = 0; i < request->entries_size(); ++i) {
		const long long index = request->entries(i).entryindex();
		LogArray &log = state_.log;

		Entry cpp_entry;
		cpp_entry.term = request->entries(i).term();
		cpp_entry.entryIndex = request->entries(i).entryindex();
		cpp_entry.command = request->entries(i).command();
		cpp_entry.key = request->entries(i).key();
		cpp_entry.val = request->entries(i).val();
		cpp_entry.replyerId = request->entries(i).replyerid();
		cpp_entry.prmIndex = request->entries(i).prmindex();

		if (!log.has(index)) {
			log.insert(cpp_entry, index);
		} else if (log.has(index) && log.at(index).term != cpp_entry.term) {
			log.flushToEnd(index);
			log.insert(cpp_entry, index);
		} else if (log.has(index) && log.at(index).term == cpp_entry.term)
			continue;  /// add for completeness.
	}
	logMasterLk.unlock();

	boost::unique_lock<boost::shared_mutex> cmtIdxLk(state_.cmtIdxMtx);
	if (request->leadercommit() > state_.commitIndex) {
		long long tmp_commit_index = std::min(request->leadercommit(), state_.log.back().entryIndex);
		if (state_.commitIndex < tmp_commit_index) {
			state_.commitIndex = tmp_commit_index;
			cmtIdxLk.unlock();
			apply_queue.notify();
		}
	}

	boost::unique_lock<boost::shared_mutex> lk3(state_.curTermMtx);

	if (request->term() > state_.currentTerm) {
		state_.currentTerm = request->term();
		lk3.unlock();
		identity_transformer(FollowerNo);
	} else {
		lk3.unlock();
		if (state_.currentIdentity == CandidateNo) identity_transformer(FollowerNo);
		else timer_.Reset();
	}
#endif
}

void SJTU::IdentityBase::ProcsRequestVoteFunc(const PbRequestVoteRequest *request, PbRequestVoteResponse *response) {
	boost::timer t;
	while (paused) {
		if (t.elapsed() * 1000 > PEER_TIMEOUT_MILLISECOND)
			return;
		std::this_thread::yield();
	}
//	printf("%lf\n", t.elapsed());


	fprintf(stderr, "server %s is processing request vote function\n", info.get_local().toString().c_str());

	boost::unique_lock<boost::shared_mutex> lk1(state_.curTermMtx, boost::defer_lock);
	boost::unique_lock<boost::shared_mutex> lk2(state_.votedForMtx, boost::defer_lock);
	boost::lock(lk1, lk2);

	if (request->term() > state_.currentTerm) {
		state_.votedFor.clear();
	}

//	fprintf(stderr, "serverId %s is processing requestVote RPC, Identity %d\n", info.get_local().toString().c_str(),
//					state_.currentIdentity);
	/**
	 * Default implementation.
	 * */

	response->set_term(state_.currentTerm);
	response->set_votegranted(true);

#ifdef _NOT_TRIVIAL_VOTE
	if (request->term() < state_.currentTerm)
		response->set_votegranted(false);

	/// "if votedFor is null or candidateId, and candidate's log is at least up-to-date as receiver's log, grant vote."
	/// if this server has voted for others, refuse to grant vote.
	if (!state_.votedFor.empty() && state_.votedFor.toString() != request->candidateid())
		response->set_votegranted(false);

	/**
	 * "Raft determines which of two logs is more up-to-date by comparing the index and term of the last entries in the logs.
	 * If the logs have last entries with different terms, then the log with the later term is more up-to-date.
	 * If the logs end with the same term, then whichever log is longer is more up-to-date.
	 * */
	/// or candidate's log is out-of-date, reject.
	boost::shared_lock<boost::shared_mutex> lk(state_.logMasterMtx);

	if (request->lastlogterm() != state_.log.back().term) {
		if (state_.log.back().term > request->lastlogterm()) {    /// my log is newer.
			response->set_votegranted(false);
		}
	} else {
		if (state_.log.back().entryIndex > request->lastlogindex())    /// my log is longer.
			response->set_votegranted(false);
	}
	lk.unlock();

	if (response->votegranted()) {
		state_.votedFor = ServerId(request->candidateid());
	}

	if (request->term() > state_.currentTerm) {
		state_.currentTerm = request->term();
		lk1.unlock();
		lk2.unlock();
		identity_transformer(FollowerNo);
	} else {
		lk1.unlock();
		lk2.unlock();
		if (response->votegranted()) timer_.Reset();
	}
#else
	std::cerr << "this voteGranted rule is for demonstration" << std::endl;
	if (!state_.votedFor.empty() && state_.votedFor.toString() != request->candidateid())
		response->set_votegranted(false);
	else {
		response->set_votegranted(true);
		ServerId vf(request->candidateid());
		state_.votedFor = vf;
	}
#endif
}

/// default implementation is for follower and candidate.
void IdentityBase::ProcsClientFunc(const PbClientRequest *request, PbClientResponse *response) {
	boost::timer t;
	while (paused) {
		if (t.elapsed() * 1000 > PEER_TIMEOUT_MILLISECOND)
			return;
		std::this_thread::yield();
	}
//	printf("%lf\n", t.elapsed());

	/**
	 * Receive from client
	 * */
	if (request->senderid().empty()) {
		ProcsClientFromClient(request, response);
	} else {
		ProcsClientFromPeer(request, response);
	}

}

void IdentityBase::ProcsClientFromClient(const PbClientRequest *request, PbClientResponse *response) {
//	fprintf(stderr, "server %s is processing client put function\n", info.get_local().toString().c_str());
	/**
	 * increment promise index, store promise and cache future handle.
	 * */
//	static int cnt = 0;
	boost::unique_lock<boost::shared_mutex> repoIdxLk(state_.prmRepoIdxMtx);
	long long cur_prm_index = state_.prmRepoIdx++;
	repoIdxLk.unlock();
	/// things are ok here.
//	printf("server id %s, current promise index: %lld\n", info.get_local().toString().c_str(), cur_prm_index);

	std::promise<std::string> prm;
	std::future<std::string> fut = prm.get_future();
	boost::unique_lock<boost::shared_mutex> repoLk(state_.prmRepoMtx);
	state_.prmRepo[cur_prm_index] = std::move(prm);
//	state_.prmRepo.insert(std::pair<long long, std::promise<std::string> >(cur_prm_index, std::move(prm)));
	repoLk.unlock();

	/// launch server_ends to peers.
	std::vector<std::unique_ptr<RaftPeerClientImpl> > tmp_client_ends;
	for (const ServerId &srv_id : info.get_srvList()) {
		if (srv_id == info.get_local()) continue;
		tmp_client_ends.push_back(std::make_unique<RaftPeerClientImpl>(srv_id));
	}

	boost::atomic<std::size_t> count_success{0};
	/// broadcast requests, retry for five times if fail.
	/**
	 * This kind of retry may cause replicated element inside our map, it's horrible.
	 * */

	int retry_time = 5;
	for (int t = 0; t < retry_time; ++t) {
//		printf("times %d\n", cnt++);
		for (size_t i = 0; i < tmp_client_ends.size(); ++i) {
			tmp_client_ends[i]->th = boost::thread([&, i]() mutable {

				PbClientRequest redirect_rqs;
				redirect_rqs.set_command(request->command());
				redirect_rqs.set_key(request->key());
				redirect_rqs.set_val(request->val());
				/// set senderId this time.
				redirect_rqs.set_senderid(info.get_local().toString());
				redirect_rqs.set_prmindex(cur_prm_index);

				PbClientResponse redirect_rsp;
				grpc::ClientContext context;
				context.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(PEER_TIMEOUT_MILLISECOND));
				grpc::Status status = tmp_client_ends[i]->stub_->ClientRPC(&context, redirect_rqs, &redirect_rsp);
				if (!status.ok()) {
//					fprintf(stderr, "IdentityBase ProcsPutFunc error, error code: %d, error msg: %s\n", status.error_code(),
//									status.error_message().c_str());
				} else {
					if (redirect_rsp.success()) ++count_success;
				}
			});
		}
		for (size_t i = 0; i < tmp_client_ends.size(); ++i) {
			tmp_client_ends[i]->th.join();
		}
		fprintf(stderr, "count success: %d\n", (int) count_success);
		if (count_success > 1)
			throw std::runtime_error("two leaders add log");
		else if (count_success == 1) {
			break;
		}
		boost::this_thread::yield();
		boost::this_thread::sleep_for(boost::chrono::milliseconds(info.get_electionTimeout() * 2 / retry_time));
	}

	/**
	 * block until finish
	 * */
	if(count_success == 1) {
		response->set_replymsg(fut.get());
		response->set_success(true);
	}
	else {
		char reply[100];
		sprintf(reply, "Client request respond time exceeded, retry %d times, no leader is found", retry_time);
		response->set_replymsg(std::string(reply));
		response->set_success(false);
	}
}

void IdentityBase::ProcsClientFromPeer(const PbClientRequest *request, PbClientResponse *response) {
	response->set_success(false);
}
};
