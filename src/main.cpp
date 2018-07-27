#include <string>
#include "../include/server.h"

int main() {
	std::string config_filename = "raft_0.json";
	SJTU::Server server(config_filename);
	return 0;
}