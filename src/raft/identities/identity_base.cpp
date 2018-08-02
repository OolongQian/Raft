#include "../../../include/raft/identities/identity_base.h"

//#define _NOT_TRIVIAL_VOTE
#define _NOT_TRIVIAL_APPEND

namespace SJTU {

	void
	SJTU::IdentityBase::ProcsAppendEntriesFunc(const PbAppendEntriesRequest *request, PbAppendEntriesResponse *response) {
//		AppendEntriesSelfModification(request);
		fprintf(stderr, "server %s get appendEntriesRPC from %s\n", info.get_local().toString().c_str(),
						request->leaderid().c_str());
		AppendEntriesResponseGeneration(request, response);
		fprintf(stderr, "return response: term %lld, success %d\n", response->term(), (int) response->success());
	}

	void SJTU::IdentityBase::ProcsRequestVoteFunc(const PbRequestVoteRequest *request, PbRequestVoteResponse *response) {
//		RequestVoteSelfModification(request);
		fprintf(stderr, "server %s get appendEntriesRPC from %s\n", info.get_local().toString().c_str(),
						request->candidateid().c_str());
		RequestVoteResponseGeneration(request, response);
		fprintf(stderr, "return response: term %lld, vote %d\n", response->term(), (int) response->votegranted());
	}

	void IdentityBase::AppendEntriesResponseGeneration(const PbAppendEntriesRequest *request,
																										 PbAppendEntriesResponse *response) {
		/**
		 * Default implementation.
		 * */
//		fprintf(stderr, "appendEntriesRequest is received...Always respond success\n");

		response->set_term(state_.currentTerm);
		response->set_success(true);

#ifdef _NOT_TRIVIAL_APPEND
		/// reply false if request is out of date.
		if (request->term() < state_.currentTerm)
			response->set_success(false);
		/// reply false if log doesn't contain an entry at prevLogIndex whose term matches prevLogTerm.
		if (!state_.log.has(request->prevlogindex()) ||
				state_.log.at(request->prevlogindex()).term != request->prevlogterm())
			response->set_success(false);

		if (request->entries_size() == 0) {
			printf("receive empty entries (heartbeat), return...\n");
			return;
		}

		/// if an existing entry conflicts with a new one (same index but different terms), delete the existing entry and all that follow it.
		/// append any new entries not already in the log.
		/// note that entryIndex should be monotonically increasing.
		for (int i = 0; i < request->entries_size(); ++i) {
			const long long &index = request->entries(i).entryindex();
			LogArray &log = state_.log;

			Entry cpp_entry;
			cpp_entry.term = request->entries(i).term();
			cpp_entry.entryIndex = request->entries(i).entryindex();
			cpp_entry.command = request->entries(i).command();
			cpp_entry.key = request->entries(i).key();
			cpp_entry.val = request->entries(i).val();

			if (!log.has(index)) {
				log.insert(cpp_entry, index);
			} else if (log.has(index) && log.at(index).term != cpp_entry.term) {
				log.flushToEnd(index);
				log.insert(cpp_entry, index);
			} else if (log.has(index) && log.at(index).term == cpp_entry.term)
				continue;  /// add for completeness.
		}
		if (request->leadercommit() > state_.commitIndex) {
			state_.commitIndex = std::min(request->leadercommit(),
																		request->entries(request->entries_size() - 1).entryindex());
		}
#endif

	}

	void
	IdentityBase::RequestVoteResponseGeneration(const PbRequestVoteRequest *request, PbRequestVoteResponse *response) {
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
		if(request->lastlogterm() != state_.log.back().term) {
			if(state_.log.back().term > request->lastlogterm()) {		/// my log is newer.
				response->set_votegranted(false);
			}
		}
		else {
			if(state_.log.back().entryIndex > request->lastlogindex())		/// my log is longer.
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
	}

	void IdentityBase::AppendEntriesSelfModification(const PbAppendEntriesRequest *request) {
		/// if commitIndex > lastApplied: increment lastApplied, apply log[lastApplied] to state machine.
		/// oh I suddenly realize that this should be automated by apply_queue!!!
		if (request->term() > state_.currentTerm) {
			state_.currentTerm = request->term();
			state_.votedFor.clear();
			identity_transformer(FollowerNo);
		}
	}

	void IdentityBase::RequestVoteSelfModification(const PbRequestVoteRequest *request) {
		if (request->term() > state_.currentTerm) {
			state_.currentTerm = request->term();
			state_.votedFor.clear();
			identity_transformer(FollowerNo);
		}
	}

	void IdentityBase::ProcsAddLogFunc(const PbAddLogRequest *, PbAddLogResponse *) {

	}
};
