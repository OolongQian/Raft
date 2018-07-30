#ifndef RAFT_PROJ_RAFT_PEER_CLIENT_H
#define RAFT_PROJ_RAFT_PEER_CLIENT_H

#include "raft_peer.grpc.pb.h"
#include "../../common.h"

#include <iostream>
#include <memory>
#include <cstring>
#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <boost/thread.hpp>

namespace SJTU {
	class RaftPeerClientImpl {
	public:
		explicit RaftPeerClientImpl(const std::shared_ptr<grpc::Channel> &channel, ServerId id) :
				stub_(RaftPeerService::NewStub(channel)), id(id) {}

		~RaftPeerClientImpl() {
			if (th.joinable()) th.join();
		}

		std::unique_ptr<RaftPeerService::Stub> stub_;
		boost::thread th;
		ServerId id;
	};
};
#endif //RAFT_PROJ_RAFT_PEER_CLIENT_H
