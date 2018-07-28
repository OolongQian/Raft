
#include <grpcpp/support/status.h>
#include <grpcpp/server_context.h>
#include "../../../include/raft/raft_proto/raft_peer.pb.h"
#include "../../../include/raft/raft_proto/raft_peer_service.h"

namespace SJTU {


	RaftPeerServiceImpl::RaftPeerServiceImpl() {

	}

	grpc::Status
	RaftPeerServiceImpl::AppendEntriesRPC(grpc::ServerContext *context, const PbAppendEntriesRequest *request,
																				PbAppendEntriesResponse *response) {
		CppAppendEntriesResponse cpp_response = appendEntriesFunc(CppAppendEntriesRequest(*request));
		*response = cpp_response.Convert();
		return grpc::Status::OK;
	}

	grpc::Status RaftPeerServiceImpl::RequestVoteRPC(grpc::ServerContext *context, const PbRequestVoteRequest *request,
																									 PbRequestVoteResponse *response) {
		CppRequestVoteResponse cpp_response = requestVoteFunc(CppRequestVoteRequest(*request));
		*response = cpp_response.Convert();
		return grpc::Status::OK;
	}


};
