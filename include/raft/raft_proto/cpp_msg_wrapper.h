#ifndef RAFT_PROJ_CPP_MSG_WRAPPER_H
#define RAFT_PROJ_CPP_MSG_WRAPPER_H

/**
 * We have defined rpc calls in proto files, and protocol compiler helps
 * us generate interfaces for those msg classes, but they are still difficult
 * to use and cannot serve as a data wrapper inside our raft implementation.
 *
 * Therefore we had better create such data wrappers in cpp version and define
 * some functions to convert between them.
 * */
#include "../../log/entry.h"
#include "raft_peer.pb.h"
#include "../../server_info.h"

namespace SJTU {

	struct CppAppendEntriesRequest {
		long long term;
		ServerId leaderId;
		long long prevLogIndex;
		long long prevLogTerm;
		std::vector<Entry> entries;
		long long leaderCommit;

		CppAppendEntriesRequest() = default;

		CppAppendEntriesRequest(long long term, ServerId leaderId, long long prevLogIndex, long long prevLogTerm,
														std::vector<Entry> entries, long long leaderCommit) :
				term(term), leaderId(std::move(leaderId)), prevLogIndex(prevLogIndex), prevLogTerm(prevLogTerm),
				entries(std::move(entries)), leaderCommit(leaderCommit) {}

		explicit CppAppendEntriesRequest(const PbAppendEntriesRequest &request) : term(request.term()),
																																							leaderId(request.leaderid()),
																																							prevLogIndex(request.prevlogindex()),
																																							prevLogTerm(request.prevlogterm()),
																																							leaderCommit(request.leadercommit()) {
			entries.clear();
			for (int i = 0; i < request.entries_size(); ++i) {
				entries.emplace_back(request.entries(i));
			}
		}

		PbAppendEntriesRequest Convert() {
			PbAppendEntriesRequest request;
			request.set_term(term);
			request.set_leaderid(leaderId.toString());
			request.set_prevlogindex(prevLogIndex);
			request.set_prevlogterm(prevLogTerm);
			for (const Entry &entry : entries) {
				PbAppendEntriesRequest_Entry *elem = request.add_entries();
				elem->set_command(entry.command);
				elem->set_key(entry.key);
				elem->set_val(entry.val);
				elem->set_term(entry.term);
				elem->set_entryindex(entry.entryIndex);
			}
			request.set_leadercommit(leaderCommit);
			return request;
		}
	};

	struct CppAppendEntriesResponse {
		long long term;
		bool success;

		CppAppendEntriesResponse() = default;

		CppAppendEntriesResponse(long long term, bool success) : term(term), success(success) {}

		explicit CppAppendEntriesResponse(const PbAppendEntriesResponse &response) : term(response.term()),
																																								 success(response.success()) {}

		PbAppendEntriesResponse Convert() {
			PbAppendEntriesResponse response;
			response.set_term(term);
			response.set_success(success);
			return response;
		}
	};

	struct CppRequestVoteRequest {
		long long term;
		ServerId candidateId;
		long long lastLogIndex;
		long long lastLogTerm;

		CppRequestVoteRequest() = default;

		CppRequestVoteRequest(long long term, ServerId candidateId, long long lastLogIndex, long long lastLogTerm) :
				term(term), candidateId(std::move(candidateId)), lastLogIndex(lastLogIndex), lastLogTerm(lastLogTerm) {}

		explicit CppRequestVoteRequest(const PbRequestVoteRequest &request) : term(request.term()),
																																					candidateId(request.candidateid()),
																																					lastLogIndex(request.lastlogindex()),
																																					lastLogTerm(request.lastlogterm()) {}

		PbRequestVoteRequest Convert() {
			PbRequestVoteRequest request;
			request.set_term(term);
			request.set_candidateid(candidateId.toString());
			request.set_lastlogindex(lastLogIndex);
			request.set_lastlogterm(lastLogTerm);
			return request;
		}
	};

	struct CppRequestVoteResponse {
		long long term;
		bool voteGranted;

		CppRequestVoteResponse() = default;

		explicit CppRequestVoteResponse(const PbRequestVoteResponse &request) :
				term(request.term()), voteGranted(request.votegranted()) {}

		PbRequestVoteResponse Convert() {
			PbRequestVoteResponse response;
			response.set_votegranted(voteGranted);
			response.set_term(term);
			return response;
		}
	};
};

#endif //RAFT_PROJ_CPP_MSG_WRAPPER_H
