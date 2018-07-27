#include "server.h"
#include <thread>
#include <string>

int main() {
	std::string config_filename = "raft_0.json";
	SJTU::Server server(config_filename);
	server.StartUp();
	std::this_thread::sleep_for(std::chrono::seconds(10));
	server.ShutDown();
	return 0;

}