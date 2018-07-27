
#include <grpcpp/support/status.h>
#include <grpcpp/server_context.h>
#include "../../../include/raft/raft_proto/raft_peer.pb.h"
#include "../../../include/raft/raft_proto/raft_peer_service.h"

namespace SJTU {

	SJTU::RaftPeerServiceImpl::RaftPeerServiceImpl() {

	}

	grpc::Status
	SJTU::RaftPeerServiceImpl::AppendEntriesRPC(grpc::ServerContext *context, const PbAppendEntriesRequest *request,
																							PbAppendEntriesResponse *response) {
		return Service::AppendEntriesRPC(context, request, response);
	}

	grpc::Status
	SJTU::RaftPeerServiceImpl::RequestVoteRPC(grpc::ServerContext *context, const PbRequestVoteRequest *request,
																						PbRequestVoteResponse *response) {
		return Service::RequestVoteRPC(context, request, response);
	}
};