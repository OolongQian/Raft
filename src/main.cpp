#include <string>
#include "../include/server.h"

int main() {
	std::string config_filename = "shit";
	SJTU::Server server(config_filename);
	return 0;
}