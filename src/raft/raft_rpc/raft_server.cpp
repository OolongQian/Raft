#include "../../../include/raft/raft_rpc/raft_server.h"
#include "../../../include/raft/raft_proto/cpp_msg_wrapper.h"
#include "../../../include/raft/raft_rpc/raft_server.h"

namespace SJTU {

	void SJTU::RaftServer::BindServiceFunc(std::function<CppRequestVoteResponse(CppRequestVoteRequest)> f1,
																				 std::function<CppAppendEntriesResponse(CppAppendEntriesRequest)> f2) {

	}

	void SJTU::RaftServer::AsycRun() {

	}
}