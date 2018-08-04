#include "../../../include/raft/identities/identity_base.h"

#define _NOT_TRIVIAL_VOTE
#define _NOT_TRIVIAL_APPEND

namespace SJTU {

void
SJTU::IdentityBase::ProcsAppendEntriesFunc(const PbAppendEntriesRequest *request, PbAppendEntriesResponse *response) {
//		AppendEntriesSelfModification(request);
//	if (info.get_local().toString() == "127.0.0.1:50001") {
//		fprintf(stderr, "follower receives request entry size: %d\n", request->entries_size());
//	}
//	fprintf(stderr, "server %s get appendEntriesRPC from %s\n", info.get_local().toString().c_str(),
//					request->leaderid().c_str());
	response->set_inconsist(false);
	/**
	 * Default implementation.
	 * */
//		fprintf(stderr, "appendEntriesRequest is received...Always respond success\n");
//	fprintf(stderr, "follower or candidate AppendEntries received\n");
	fprintf(stderr, "term: %lld leader: %s prevLogIndex: %lld prevLogTerm: %lld LeaderCommit: %lld\n", request->term(),
					request->leaderid().c_str(), request->prevlogindex(), request->prevlogterm(), request->leadercommit());
	response->set_term(state_.currentTerm);
	response->set_success(true);

#ifdef _NOT_TRIVIAL_APPEND
	/// reply false if request is out of date.
	if (request->term() < state_.currentTerm)
		response->set_success(false);
	/// reply false if log doesn't contain an entry at prevLogIndex whose term matches prevLogTerm.
	std::cout << request->prevlogterm() << ' ' << request->prevlogindex() << std::endl;

	if (!state_.log.has(request->prevlogindex()) ||
			state_.log.at(request->prevlogindex()).term != request->prevlogterm()) {
//		fprintf(stderr, "heartbeat inconsistency\n");
		response->set_inconsist(true);
		response->set_success(false);
		return;
	}

	if (request->entries_size() == 0) {
//		printf("receive empty entries (heartbeat), return...\n");
//		return;
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
			response->set_inconsist(true);
			log.flushToEnd(index);
			log.insert(cpp_entry, index);
		} else if (log.has(index) && log.at(index).term == cpp_entry.term)
			continue;  /// add for completeness.
	}
//	printf("current follower %s log length %d\n", info.get_local().toString().c_str(), state_.log.length());
//	printf("follower's commit index update %d %d\n", request->leadercommit(), state_.log.back().entryIndex);
	if (request->leadercommit() > state_.commitIndex) {
		long long tmp_commit_index = std::min(request->leadercommit(), state_.log.back().entryIndex);
		if (state_.commitIndex < tmp_commit_index) {
			state_.commitIndex = tmp_commit_index;
			apply_queue.notify();
		}
	}
#endif
//	fprintf(stderr, "return response: term %lld, success %d\n", response->term(), (int) response->success());
}

void SJTU::IdentityBase::ProcsRequestVoteFunc(const PbRequestVoteRequest *request, PbRequestVoteResponse *response) {
//		RequestVoteSelfModification(request);
//	fprintf(stderr, "server %s get appendEntriesRPC from %s\n", info.get_local().toString().c_str(),
//					request->candidateid().c_str());
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
	if (request->lastlogterm() != state_.log.back().term) {
		if (state_.log.back().term > request->lastlogterm()) {    /// my log is newer.
			response->set_votegranted(false);
		}
	} else {
		if (state_.log.back().entryIndex > request->lastlogindex())    /// my log is longer.
			response->set_votegranted(false);
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
//	fprintf(stderr, "return response: term %lld, vote %d\n", response->term(), (int) response->votegranted());
}

/// default implementation is for follower and candidate.
void IdentityBase::ProcsPutFunc(const PbPutRequest *request, PbPutResponse *response) {
	/**
	 * Receive from client
	 * */
	if (request->senderid().empty()) {
		ProcsClientPutFunc(request, response);
	} else {
		ProcsPeerPutFunc(request, response);
	}

}

void IdentityBase::ProcsClientPutFunc(const PbPutRequest *request, PbPutResponse *response) {
	/**
	 * increment promise index, store promise and cache future handle.
	 * */
	static int cnt = 0;
	long long cur_prm_index = state_.prmRepoIdx++;
	std::promise<std::string> prm;
	std::future<std::string> fut = prm.get_future();
	state_.prmRepo.insert(std::pair<long long, std::promise<std::string> >(cur_prm_index, std::move(prm)));

	/// launch server_ends to peers.
	std::vector<std::unique_ptr<RaftPeerClientImpl> > tmp_client_ends;
	for (const ServerId &srv_id : info.get_srvList()) {
		if (srv_id == info.get_local()) continue;
		tmp_client_ends.push_back(std::make_unique<RaftPeerClientImpl>(srv_id));
	}

	boost::atomic<std::size_t> count_success{0};
	/// broadcast requests, retry for five times if fail.
	for (int t = 0, retry_time = 5; t < retry_time; ++t) {
		printf("times %d\n", cnt++);
		for (size_t i = 0; i < tmp_client_ends.size(); ++i) {
			tmp_client_ends[i]->th = boost::thread([&, i]() mutable {
				PbPutRequest redirect_rqs;
				redirect_rqs.set_key(request->key());
				redirect_rqs.set_val(request->val());
				/// set senderId this time.
				redirect_rqs.set_senderid(info.get_local().toString());
				redirect_rqs.set_prmindex(cur_prm_index);

				grpc::ClientContext context;
				context.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(50));
				grpc::Status status = tmp_client_ends[i]->stub_->PutRPC(&context, redirect_rqs, response);
				if (!status.ok()) {
					fprintf(stderr, "IdentityBase ProcsPutFunc error, error code: %d, error msg: %s\n", status.error_code(),
									status.error_message().c_str());
				} else {
					if (response->success()) ++count_success;
				}
			});
		}
		for (size_t i = 0; i < tmp_client_ends.size(); ++i) {
			tmp_client_ends[i]->th.join();
		}
		if (count_success > 1)
			throw std::runtime_error("two leaders add log");
		else if (count_success == 1) {
			printf("new log safely accepted by leader\n");
			break;
		}
	}

	/**block until finish*/
	if(count_success == 1) {
		response->set_replymsg(fut.get());
		response->set_success(true);
	}
	else {
		fprintf(stderr, "Put request not responded\n");
		response->set_replymsg("Put request respond time exceeded");
		response->set_success(false);
	}
}

void IdentityBase::ProcsPeerPutFunc(const PbPutRequest *request, PbPutResponse *response) {
	response->set_success(false);
}
};
