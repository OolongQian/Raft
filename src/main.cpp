#include "../include/server.h"
#include <unistd.h>

int main() {
	SJTU::Server server;
	server.StartUp();

	sleep(10);
	server.ShutDown();
	return 0;
}