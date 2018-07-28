
int main() {
	std::string config_filename0 = "raft_0.json";
	std::string config_filename1 = "raft_1.json";
	std::string config_filename2 = "raft_2.json";

	SJTU::Server server0(config_filename0);
	SJTU::Server server1(config_filename1);
	SJTU::Server server2(config_filename2);

	server0.StartUp();
	server1.StartUp();
	server2.StartUp();

	sleep(20);
	server0.ShutDown();
	server1.ShutDown();
	server2.ShutDown();

	return 0;
}
