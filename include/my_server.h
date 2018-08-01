#ifndef RAFT_PROJ_MY_SERVER_H
#define RAFT_PROJ_MY_SERVER_H


#include <grpcpp/support/status.h>
#include <boost/thread.hpp>
#include <grpc++/server_builder.h>
#include <grpcpp/security/server_credentials.h>
#include "raft/raft_proto/raft_peer.grpc.pb.h"

/*
using namespace std;

class myServer {
public:
	class Foo final : public RaftPeerService::Service {

	public:
		Foo();

		grpc::Status AppendEntriesRPC(grpc::ServerContext *context, const PbAppendEntriesRequest *request,
																	PbAppendEntriesResponse *response) override ;

		grpc::Status RequestVoteRPC(grpc::ServerContext *context, const PbRequestVoteRequest *request,
																PbRequestVoteResponse *response) override ;
	};

public:
	boost::thread th;
	std::unique_ptr<grpc::Server> server;
	Foo service;

	explicit myServer(std::string id_str);
};
*/

#endif //RAFT_PROJ_MY_SERVER_H
