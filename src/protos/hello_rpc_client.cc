#include "hello.grpc.pb.h"
#include <iostream>
#include <memory>
#include <cstring>
#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

class HelloClient {
public:
	explicit HelloClient(std::shared_ptr<grpc::Channel> channel) :
			stub_(HelloService::NewStub(channel)) {}

	void SayHello(const std::string &name) {
		HelloRequest request;
		request.set_greeting(name);

		HelloResponse response;
		grpc::ClientContext context;
		stub_->SayHello(&context, request, &response);
		std::cout << "Client receives response: " << response.reply() << std::endl;
	}

private:
	std::unique_ptr<HelloService::Stub> stub_;
};

int main() {
	auto channel = grpc::CreateChannel("localhost:5000", grpc::InsecureChannelCredentials());
	HelloClient client(channel);

	client.SayHello("Worrrlllllddddddddd..........");
	return 0;
}