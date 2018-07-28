#include "../../../include/raft/raft_rpc/raft_server.h"
#include "../../../include/raft/raft_proto/cpp_msg_wrapper.h"
#include "../../../include/raft/raft_rpc/raft_server.h"

namespace SJTU {

	void RaftServer::BindServiceFunc(std::function<CppRequestVoteResponse(CppRequestVoteRequest)> f1,
																	 std::function<CppAppendEntriesResponse(CppAppendEntriesRequest)> f2) {
		server_end_.requestVoteFunc = std::move(f1);
		server_end_.appendEntriesFunc = std::move(f2);
	}

	void RaftServer::PreMonitorInit() {
		grpc::ServerBuilder builder;
		builder.AddListeningPort(serverId.toString(), grpc::InsecureServerCredentials());
		builder.RegisterService(&server_end_);  /// itself has implemented required interfaces.
		server = builder.BuildAndStart();
	}

	void RaftServer::Monitor() {
		th = boost::thread([this]() {
			std::cout << "Server listening on " << serverId.toString() << std::endl;
			server->Wait();
		});
	}

	void RaftServer::Stop() {
		printf("gracefully shutting down, and join monitoring thread...\n");
		server->Shutdown();
		th.join();
	}
};
