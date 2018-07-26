#ifndef RAFT_PROJ_RAFT_PEER_SERVER_H
#define RAFT_PROJ_RAFT_PEER_SERVER_H

#include "raft_peer.grpc.pb.h"

#include <iostream>
#include <cstring>
#include <mutex>
#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>
#include <boost/thread/lock_guard.hpp>

namespace SJTU {
	/**
	 * A class that implements interface created by gRPC
	 * */
	class RaftPeerServerImpl final : public RaftPeerService::Service {
	public:
		RaftPeerServerImpl();

		grpc::Status AppendEntriesRPC(grpc::ServerContext *context, const PbAppendEntriesRequest *request,
																	PbAppendEntriesResponse *response) override;

		grpc::Status RequestVoteRPC(grpc::ServerContext *context, const PbRequestVoteRequest *request,
																PbRequestVoteResponse *response) override;
	};
};

#endif //RAFT_PROJ_RAFT_PEER_SERVER_H
