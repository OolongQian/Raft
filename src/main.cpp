#include "../include/server.h"
#include <thread>


int main() {
	SJTU::Server server;
	server.StartUp();

	std::this_thread::sleep_for(std::chrono::seconds(10));
	server.ShutDown();
	return 0;
}