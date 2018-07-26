#ifndef RAFT_PROJ_RAFT_PEER_CLIENT_H
#define RAFT_PROJ_RAFT_PEER_CLIENT_H

#include "raft_peer.grpc.pb.h"

#include <iostream>
#include <memory>
#include <cstring>
#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

class RaftPeerClient {
public:
	explicit RaftPeerClient(const std::shared_ptr<grpc::Channel> &channel) :
			stub_(RaftPeerService::NewStub(channel)) {}

private:
	std::unique_ptr<RaftPeerService::Stub> stub_;
};

#endif //RAFT_PROJ_RAFT_PEER_CLIENT_H
