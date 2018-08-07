#include "../../../include/raft/raft_proto/raft_server.h"
#include "../../../include/raft/raft_proto/cpp_msg_wrapper.h"

namespace SJTU {

	void RaftServer::PreMonitorInit() {
		;
	}

void RaftServer::Monitor() {
	if (th.joinable()) return;
	th = boost::thread([this]() {
		grpc::ServerBuilder builder;
		builder.AddListeningPort(serverId.toString(), grpc::InsecureServerCredentials());
		builder.RegisterService(&service);  /// itself has implemented required interfaces.
		server = builder.BuildAndStart();
//			std::cout << "Server listening on " << serverId.toString() << std::endl;
		server->Wait();
	});
}


	void RaftServer::Stop() {
//		printf("gracefully shutting down, and join monitoring thread...\n");
		server->Shutdown();
		th.join();
	}

	void RaftServer::BindServiceFunc(RaftServer::RequestVoteFunc f1, RaftServer::AppendEntriesFunc f2,
																	 RaftServer::ClientFunc f3) {
		service.requestVoteFunc = std::move(f1);
		service.appendEntriesFunc = std::move(f2);
		service.clientFunc = std::move(f3);
	}

void RaftServer::Pause() {
	paused = true;
}

void RaftServer::Resume() {
	paused = false;
}

grpc::Status
	RaftServer::RaftPeerServiceImpl::AppendEntriesRPC(grpc::ServerContext *context, const PbAppendEntriesRequest *request,
																										PbAppendEntriesResponse *response) {
//		response->set_term(100);
//		printf("Append Entries RPC received\n");
		appendEntriesFunc(request, response);
		return grpc::Status::OK;
	}

	grpc::Status
	RaftServer::RaftPeerServiceImpl::RequestVoteRPC(grpc::ServerContext *context, const PbRequestVoteRequest *request,
																									PbRequestVoteResponse *response) {
//		response->set_term(100);
//		printf("Request Vote RPC received\n");
		requestVoteFunc(request, response);
		return grpc::Status::OK;
	}

grpc::Status RaftServer::RaftPeerServiceImpl::ClientRPC(grpc::ServerContext *context, const PbClientRequest *request,
																												PbClientResponse *response) {
//	printf("Put RPC received\n");
	clientFunc(request, response);
	return grpc::Status::OK;
}
};
