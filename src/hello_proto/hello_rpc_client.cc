#include "hello.grpc.pb.h"

#include <iostream>
#include <memory>
#include <cstring>
#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <grpcpp/server_builder.h>
#include "hello.grpc.pb.h"
#include <iostream>
#include <cstring>
#include <mutex>
#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>
#include <boost/thread/lock_guard.hpp>
#include <boost/thread.hpp>

class HelloImpl final : public HelloService::Service {
public:
	HelloImpl() {}

	grpc::Status SayHello(grpc::ServerContext *context, const HelloRequest *request,
												HelloResponse *response) override {
		if (request->greeting() == "fuck") {
			std::cout << "server say that you are fucked" << std::endl;
			sleep(2);
			response->set_reply("hello0 client, your msg " + request->greeting() + " is blocked");
		} else {
			response->set_reply("hello0 client, your msg is " + request->greeting());
		}
		return grpc::Status::OK;
	}
};



class HelloClient {
public:
	explicit HelloClient(std::shared_ptr<grpc::Channel> channel) :
			stub_(HelloService::NewStub(channel)) {}


	struct AsyncClientCall {
		HelloResponse response;
		grpc::ClientContext context;
		grpc::Status status;
		std::unique_ptr<grpc::ClientAsyncResponseReader<HelloResponse> > response_reader;
	};

public:
	void SayHello(const std::string &user) {
		HelloRequest request;
		request.set_greeting("greet " + user);
		AsyncClientCall *call = new AsyncClientCall;

		// 异步调用
		call->response_reader = stub_->AsyncSayHello(&call->context, request, &cq_);
		call->response_reader->Finish(&call->response, &call->status, (void *) call);
	}

	void AsyncCompleteRpc() {
		void *got_tag;
		bool ok = false;

		while (cq_.Next(&got_tag, &ok)) {
			AsyncClientCall *call = static_cast<AsyncClientCall *> (got_tag);
			if (call->status.ok()) {
				std::cout << "Greeter received: " << call->response.reply() << std::endl;
			} else {
				std::cout << "RPC failed" << std::endl;
			}
			delete call;
		}
	}
	std::unique_ptr<HelloService::Stub> stub_;
	grpc::CompletionQueue cq_;
};

int main() {
	std::string addr = "0.0.0.0:5000";
	HelloImpl service;

	grpc::ServerBuilder builder;
	builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
	builder.RegisterService(&service);
	std::unique_ptr<grpc::Server> server = builder.BuildAndStart();

	boost::thread th([&]() mutable {
		std::cout << "Server listening on " << addr << std::endl;
		server->Wait();
	});

//	boost::thread th1([&]() mutable {
//		sleep(2);
//		server->Shutdown();
//		th.interrupt();
//		th.join();
//	});
//
//	boost::thread th2([&]() mutable {
//		sleep(4);
//		grpc::ServerBuilder builder;
//		builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
//		builder.RegisterService(&service);
//		server = builder.BuildAndStart();
//		server->Wait();
//	});

	auto channel = grpc::CreateChannel("0.0.0.0:5000", grpc::InsecureChannelCredentials());
	HelloClient greeter(channel);

	boost::thread th1([&]() mutable {
		for (int i = 0; i < 10; i++) {
			sleep(1);
			grpc::ClientContext context;
			HelloRequest request;
			HelloResponse response;
			request.set_greeting("fuck");
			auto status = greeter.stub_->SayHello(&context, request, &response);
			if (status.ok()) {
				std::cout << response.reply() << std::endl;
			} else {
				std::cout << status.error_code() << ' ' << status.error_message() << std::endl;
			}
		}
	});

	boost::thread th_([&]() mutable {
		for (int i = 0; i < 10; i++) {
			sleep(1);
			grpc::ClientContext context;
			HelloRequest request;
			HelloResponse response;
			request.set_greeting("not fuck");
			auto status = greeter.stub_->SayHello(&context, request, &response);
			if (status.ok()) {
				std::cout << response.reply() << std::endl;
			} else {
				std::cout << status.error_code() << ' ' << status.error_message() << std::endl;
			}
		}
	});
	th1.join();
	th_.join();
	sleep(10);
	server->Shutdown();
	th.join();
	return 0;
}