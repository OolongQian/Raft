#include <string>
#include <boost/thread.hpp>
#include <iostream>
#include "../include/server.h"

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

int main() {
	std::string config_filename = "raft_0.json";
	SJTU::Server server(config_filename);
	server.StartUp();
	sleep(1000);
//	Foo f;
//	f.run2();
//	f.join();
//	f.run2();
//	f.join();
	return 0;
}