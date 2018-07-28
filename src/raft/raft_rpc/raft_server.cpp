#include "../../../include/raft/raft_rpc/raft_server.h"
#include "../../../include/raft/raft_proto/cpp_msg_wrapper.h"
#include "../../../include/raft/raft_rpc/raft_server.h"

namespace SJTU {

	void RaftServer::BindServiceFunc(std::function<CppRequestVoteResponse(CppRequestVoteRequest)> f1,
																	 std::function<CppAppendEntriesResponse(CppAppendEntriesRequest)> f2) {
		server_end_.requestVoteFunc = std::move(f1);
		server_end_.appendEntriesFunc = std::move(f2);
	}

	void RaftServer::Monitor() {
		th = boost::thread([this]() {
			server_end_.AsyncRun(serverId);
		});
	}
}
