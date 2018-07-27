#include <string>
#include <boost/thread.hpp>
#include <iostream>
//#include "../include/server.h"

class Foo {
public:
	boost::thread th;

	void run() {
		th = boost::thread([] { std::cout << "shit" << std::endl; });
	}

	void join() {
		if (th.joinable()) th.join();
	}
};
int main() {
//	std::string config_filename = "raft_0.json";
//	SJTU::Server server(config_filename);
	Foo f;
	f.run();
	f.join();
	return 0;
}