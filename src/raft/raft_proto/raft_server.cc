#include "../../../include/raft/raft_proto/raft_server.h"
#include "../../../include/raft/raft_proto/cpp_msg_wrapper.h"

namespace SJTU {

	void RaftServer::BindServiceFunc(std::function<CppRequestVoteResponse(CppRequestVoteRequest)> f1,
																	 std::function<CppAppendEntriesResponse(CppAppendEntriesRequest)> f2) {
//		service.requestVoteFunc = std::move(f1);
//		service.appendEntriesFunc = std::move(f2);
	}

	void RaftServer::PreMonitorInit() {
		grpc::ServerBuilder builder;
		builder.AddListeningPort(serverId.toString(), grpc::InsecureServerCredentials());
		builder.RegisterService(&service);  /// itself has implemented required interfaces.
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

	RaftServer::RaftPeerServiceImpl::RaftPeerServiceImpl() {

	}

	grpc::Status
	RaftServer::RaftPeerServiceImpl::AppendEntriesRPC(grpc::ServerContext *context, const PbAppendEntriesRequest *request,
																										PbAppendEntriesResponse *response) {
		response->set_term(100);
		return grpc::Status::OK;
	}

	grpc::Status
	RaftServer::RaftPeerServiceImpl::RequestVoteRPC(grpc::ServerContext *context, const PbRequestVoteRequest *request,
																									PbRequestVoteResponse *response) {
		response->set_term(100);
		return grpc::Status::OK;
	}
};
