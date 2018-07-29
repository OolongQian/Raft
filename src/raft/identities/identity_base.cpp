#include "../../../include/raft/identities/identity_base.h"

namespace SJTU {

	CppAppendEntriesResponse SJTU::IdentityBase::ProcsAppendEntriesFunc(const CppAppendEntriesRequest &request) {
		/**
		 * Default implementation.
		 * */
		fprintf(stderr, "appendEntriesRequest is received...Always respond success\n");
		CppAppendEntriesResponse response;
		response.term = state_.currentTerm;

		response.success = true;
		/// reply false if request is out of date.
		if (request.term < state_.currentTerm)
			response.success = false;
		/// reply false if log doesn't contain an entry at prevLogIndex whose term matches prevLogTerm.
		if (!state_.log.has(request.prevLogIndex) || state_.log.at(request.prevLogIndex).term != request.prevLogTerm)
			response.success = false;
		/// if an existing entry conflicts with a new one (same index but different terms), delete the existing entry and all that follow it.
		/// append any new entries not already in the log.
		/// note that entryIndex should be monotonically increasing.
		for (const Entry &entry : request.entries) {
			const long long &index = entry.entryIndex;
			LogArray &log = state_.log;

			if (!log.has(index)) {
				log.insert(entry, index);
			} else if (log.has(index) && log.at(index).term != entry.term) {
				log.flushToEnd(index);
				log.insert(entry, index);
			} else if (log.has(index) && log.at(index).term == entry.term)
				continue;  /// add for completeness.
		}

		if (request.leaderCommit > state_.commitIndex) {
			state_.commitIndex = std::min(request.leaderCommit, request.entries.back().entryIndex);
		}
		return response;
	}

	CppRequestVoteResponse SJTU::IdentityBase::ProcsRequestVoteFunc(const CppRequestVoteRequest &request) {
		/**
		 * Default implementation.
		 * */
		CppRequestVoteResponse response;
		response.term = state_.currentTerm;

		response.voteGranted = true;
		if (request.term < state_.currentTerm)
			response.voteGranted = false;

//		fprintf(stderr, "requestVoteRequest is received...I know nothing about up-to-date. Vote without hesitate\n");
		fprintf(stderr, "requestVoteRequest is received...I haven't updated state_.votedFor field.\n");

		/// "if votedFor is null or candidateId, and candidate's log is at least up-to-date as receiver's log, grant vote."
		/// if this server has voted for others, refuse to grant vote.
		if (!state_.votedFor.empty() && state_.votedFor != request.candidateId)
			response.voteGranted = false;

		/**
		 * "Raft determines which of two logs is more up-to-date by comparing the index and term of the last entries in the logs.
		 * If the logs have last entries with different terms, then the log with the later term is more up-to-date.
		 * If the logs end with the same term, then whichever log is longer is more up-to-date.
		 * */
		/// or candidate's log is out-of-date, reject.
		if (request.lastLogTerm != state_.log.back().term) {
			if (state_.log.back().term > request.lastLogTerm)  /// my log is newer.
				response.voteGranted = false;
		} else {
			if (state_.log.back().entryIndex > request.lastLogIndex)  /// my log is longer.
				response.voteGranted = false;
		}

		return response;
	}
};