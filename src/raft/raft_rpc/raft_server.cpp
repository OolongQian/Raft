#include "raft/raft_rpc/raft_server.h"

namespace SJTU {
	void RaftServer::BindServiceFunc(SJTU::RaftServer::RequestVoteFunc f1, SJTU::RaftServer::AppendEntriesFunc f2) {
		server_end_.requestVoteFunc = std::move(f1);
		server_end_.appendEntriesFunc = std::move(f2);
	}

	void RaftServer::AsycRun() {
		/// this address is temporarily just kidding.
		std::string addr = "0.0.0.0:5000";
		grpc::ServerBuilder builder;
		builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
		builder.RegisterService(&server_end_);
		auto server = builder.BuildAndStart();
		std::cout << "Server listening on " << addr << std::endl;
		server->Wait();
	}
}