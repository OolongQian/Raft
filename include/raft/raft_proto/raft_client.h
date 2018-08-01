#ifndef RAFT_PROJ_RAFT_PEER_CLIENT_H
#define RAFT_PROJ_RAFT_PEER_CLIENT_H

#include "raft_peer.grpc.pb.h"
#include "../../server_info.h"

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
		explicit RaftPeerClientImpl(ServerId id) :
				stub_(RaftPeerService::NewStub(grpc::CreateChannel(id.toString(), grpc::InsecureChannelCredentials()))),
				id(id) {}

//id.toString()
		~RaftPeerClientImpl() {
			th.join();
//			if (th.joinable()) th.join();
		}

		std::unique_ptr<RaftPeerService::Stub> stub_;
		boost::thread th;
		ServerId id;
	};
};

#endif //RAFT_PROJ_RAFT_PEER_CLIENT_H
