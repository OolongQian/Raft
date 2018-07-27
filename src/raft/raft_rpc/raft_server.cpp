#include "../../../include/raft/raft_rpc/raft_server.h"
#include "../../../include/raft/raft_proto/cpp_msg_wrapper.h"
#include "../../../include/raft/raft_rpc/raft_server.h"

namespace SJTU {

	void RaftServer::BindServiceFunc(std::function<CppRequestVoteResponse(CppRequestVoteRequest)> f1,
																	 std::function<CppAppendEntriesResponse(CppAppendEntriesRequest)> f2) {

	}

	void RaftServer::AsycRun() {
		grpc::ServerBuilder builder;
		builder.AddListeningPort(serverId.toString(), grpc::InsecureServerCredentials());
		builder.RegisterService(&server_end_);
		auto server = builder.BuildAndStart();
		std::cout << "Server listening on " << serverId.toString() << std::endl;
		server->Wait();
	}
}
