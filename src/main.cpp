#include <string>
#include <boost/thread.hpp>
#include <iostream>
#include "../include/server.h"

class Foo {
public:
	boost::thread th1;
	boost::thread th2;

	void run() {
		sleep(1);
		std::cout << "hehehhehe" << std::endl;
	}

	void run2() {
		th1 = boost::thread([this] {
			run();
		});
		th2 = boost::thread([this] {
			run();
		});
	}

	void join() {
		if (th1.joinable()) th1.join();
		if (th2.joinable()) th2.join();
	}
};
int main() {
	std::string config_filename = "raft_0.json";
	SJTU::Server server(config_filename);
	sleep(100);
//	Foo f;
//	f.run2();
//	f.join();
	return 0;
}