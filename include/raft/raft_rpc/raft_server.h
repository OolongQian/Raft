#ifndef RAFT_PROJ_RAFT_SERVER_H
#define RAFT_PROJ_RAFT_SERVER_H

#include "../raft_proto/cpp_msg_wrapper.h"
#include "../raft_proto/raft_peer_service.h"
#include "../../common.h"
#include <functional>

namespace SJTU {
	class RaftServer {
		using RequestVoteFunc = std::function<CppRequestVoteResponse(CppRequestVoteRequest)>;
		using AppendEntriesFunc = std::function<CppAppendEntriesResponse(CppAppendEntriesRequest)>;

	public:
		explicit RaftServer(const ServerId &id) : serverId(id) {}

		void BindServiceFunc(RequestVoteFunc f1, AppendEntriesFunc f2);

		void AsycRun();

	private:
		const ServerId &serverId;
		RaftPeerServiceImpl server_end_;
	};
};

#endif //RAFT_PROJ_RAFT_SERVER_H
