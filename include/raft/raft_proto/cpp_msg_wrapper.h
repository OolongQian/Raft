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
#include "../../log/log.h"
#include "raft_peer.pb.h"
#include "../../server_info.h"

namespace SJTU {
	struct CppAppendEntriesRequest {
		int term;
		ServerId leaderId;
		int prevLogIndex;
		int prevLogTerm;
		Log *entries;
		int leaderCommit;

		CppAppendEntriesRequest() = default;

		explicit CppAppendEntriesRequest(PbAppendEntriesRequest) {
			;
		}

		PbAppendEntriesRequest Convert() {
			return PbAppendEntriesRequest();
		}
	};

	struct CppAppendEntriesResponse {
		int term;
		bool success;

		CppAppendEntriesResponse() = default;

		explicit CppAppendEntriesResponse(PbAppendEntriesResponse) {
			;
		}

		PbAppendEntriesResponse Convert() {
			return PbAppendEntriesResponse();
		}
	};

	struct CppRequestVoteRequest {
		int term;
		ServerId candidateId;
		int lastLogIndex;
		int lastLogTerm;

		CppRequestVoteRequest() = default;

		CppRequestVoteRequest(int term, ServerId candidateId, int lastLogIndex, int lastLogTerm) :
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
		int term;
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
