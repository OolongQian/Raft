#ifndef RAFT_PROJ_RAFT_SERVER_H
#define RAFT_PROJ_RAFT_SERVER_H

#include <raft/raft_proto/raft_peer_service.h>

namespace SJTU {
	class RaftServer {
		using RequestVoteFunc = std::function<CppRequestVoteResponse(CppRequestVoteRequest)>;
		using AppendEntriesFunc = std::function<CppAppendEntriesResponse(CppAppendEntriesRequest)>;
	public:
		void BindServiceFunc(RequestVoteFunc f1, AppendEntriesFunc f2);

		void AsycRun();

	private:
		RaftPeerServiceImpl server_end_;
	};
};

#endif //RAFT_PROJ_RAFT_SERVER_H
