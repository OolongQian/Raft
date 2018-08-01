#include "../include/my_server.h"
/*
grpc::Status myServer::Foo::AppendEntriesRPC(grpc::ServerContext *context, const PbAppendEntriesRequest *request,
																						 PbAppendEntriesResponse *response) {
	cout << "hahah " << endl;
	response->set_term(100);
	cout << "hahah " << endl;
	response->set_success(true);
	return grpc::Status::OK;
}

grpc::Status myServer::Foo::RequestVoteRPC(grpc::ServerContext *context, const PbRequestVoteRequest *request,
																					 PbRequestVoteResponse *response) {
	cout << "hahah " << endl;
	response->set_term(100);
	cout << "hahah " << endl;
	response->set_votegranted(true);
	return grpc::Status::OK;
}

myServer::Foo::Foo() {

}


myServer::myServer(std::string id_str) {
	grpc::ServerBuilder builder;
	builder.AddListeningPort(id_str, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	server = builder.BuildAndStart();
	th = boost::thread([&] {
		std::cout << "Server listening on " << id_str << std::endl;
		server->Wait();
	});
}
 */