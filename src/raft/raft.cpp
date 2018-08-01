#include "../../include/raft/raft.h"

namespace SJTU {

	Raft::Raft(const ServerInfo &info, std::map<std::string, std::string> &data) :
			server_end(info.get_local()), info(info), applyQueue(data, state) {
		/// identity
		std::function<void(int)> transformer = std::bind(&Raft::IdentityTransform, this, std::placeholders::_1);
		identities[FollowerNo] = std::make_unique<Follower>(state, timer, transformer, client_ends, info);
		identities[CandidateNo] = std::make_unique<Candidate>(state, timer, transformer, client_ends, info);
		identities[LeaderNo] = std::make_unique<Leader>(state, timer, transformer, client_ends, info);
		currentIdentity = DownNo;
	}

	void Raft::IdentityTransform(IdentityNo identityNo) {
		/// Note this!!!
		if (currentIdentity == identityNo) {
			timer.Reset();
			return;
		}

		RaftDebugContext &debugContext = GetDebug();
		debugContext.before_tranform(currentIdentity, identityNo);
		eventQueue.addEvent([this, identityNo]() mutable {
			printf("transform from %d to %d\n", currentIdentity, identityNo);
			if (currentIdentity != DownNo)
				identities[currentIdentity]->leave();
			currentIdentity = identityNo;
			identities[currentIdentity]->init();
		});
	}

	CppAppendEntriesResponse Raft::ProcsAppendEntriesAdapter(CppAppendEntriesRequest request) {
		return identities[currentIdentity]->ProcsAppendEntriesFunc(request);
	}

	CppRequestVoteResponse Raft::ProcsRequestVoteAdapter(CppRequestVoteRequest request) {
		return identities[currentIdentity]->ProcsRequestVoteFunc(request);
	}

	void Raft::TimeOutActionAdapter() {
		identities[currentIdentity]->TimeOutFunc();
	}
};