#include <string>
#include <boost/thread.hpp>
#include <iostream>
#include "../include/server.h"

#include "./hello_proto/hello.grpc.pb.h"
#include "./hello_proto/hello_rpc_server.cc"

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

class Foo {
public:
	boost::thread th1;
	boost::thread th2;

	void run() {
		try {
			boost::this_thread::interruption_point();

			sleep(1);

			std::cout << "hehehhehe" << std::endl;

//			sleep(10);
		}
		catch (boost::thread_interrupted &e) {
			std::cout << "thread is interrupted" << std::endl;
			return;
		}
	}

	void run2() {
		th2 = boost::thread([this] {
			run();
		});
		sleep(1);
		th2.interrupt();
	}

	void join() {
		if (th1.joinable()) th1.join();
		if (th2.joinable()) th2.join();
	}
};

struct Shit {
private:
	std::string s1;
	std::string s2;
public:
	bool operator<(const Shit &other) {
		return s1 < other.s1;
	}
};

/*
int main() {
	std::string config_filename0 = "raft_0.json";
	std::string config_filename1 = "raft_1.json";
	std::string config_filename2 = "raft_2.json";
//
	SJTU::Server server0(config_filename0);
	SJTU::Server server1(config_filename1);
//	SJTU::Server server2(config_filename2);

	server0.Init();  /// make raft logic.
	server1.Init();
//	server2.Init();
//
	server0.StartUp();
	server1.StartUp();
//	server2.StartUp();
//
	sleep(1000);
	server0.ShutDown();
	server1.ShutDown();
//	server2.ShutDown();

	return 0;
}
*/