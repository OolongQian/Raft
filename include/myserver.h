#ifndef RAFT_PROJ_MYSERVER_H
#define RAFT_PROJ_MYSERVER_H


#include <grpcpp/support/status.h>
#include <boost/thread.hpp>
#include <grpc++/server_builder.h>
#include <grpcpp/security/server_credentials.h>
#include "raft/raft_proto/raft_peer.grpc.pb.h"

using namespace std;


class myServer {
public:
	class Foo final : public RaftPeerService::Service {

	public:
		Foo() {}

		grpc::Status AppendEntriesRPC(grpc::ServerContext *context, const PbAppendEntriesRequest *request,
																	PbAppendEntriesResponse *response) override {
			cout << "hahah " << endl;
			response->set_term(100);
			cout << "hahah " << endl;
			response->set_success(true);
			return grpc::Status::OK;
		}

		grpc::Status RequestVoteRPC(grpc::ServerContext *context, const PbRequestVoteRequest *request,
																PbRequestVoteResponse *response) override {
			cout << "hahah " << endl;
			response->set_term(100);
			cout << "hahah " << endl;
			response->set_votegranted(true);
			return grpc::Status::OK;
		}
	};

public:
	boost::thread th;
	std::unique_ptr<grpc::Server> server;
	Foo service;

	myServer(std::string id_str) {
		grpc::ServerBuilder builder;
		builder.AddListeningPort(id_str, grpc::InsecureServerCredentials());
		builder.RegisterService(&service);
		server = builder.BuildAndStart();
		th = boost::thread([&] {
			std::cout << "Server listening on " << id_str << std::endl;
			server->Wait();
		});
	}
};


#endif //RAFT_PROJ_MYSERVER_H
