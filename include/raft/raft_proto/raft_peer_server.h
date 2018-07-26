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
	class RaftPeerServiceImpl final : public RaftPeerService::Service {
	public:

	};
};

#endif //RAFT_PROJ_RAFT_PEER_SERVER_H
