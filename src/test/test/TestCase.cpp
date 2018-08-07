#include "IdentityTestHelper.h"
#include "../../../include/raft/raft_proto/raft_server.h"
#include "../../../src/raft/raft.cpp"
#include "../../../include/my_server.h"

namespace SJTU {

/**
 * This test case initializes 1 server. It can transform from follower to candidate.
 * */
void Follower_Basic() {
	printf("Follower_basic test...\n");
	IdentityTestHelper helper;
	auto p = helper.makeServers(1);
	p[0]->Init();

	RaftDebugContext &debugContext = p[0]->GetCtx();
	std::atomic<int> follower2Candidate{0};
	debugContext.before_tranform = [&follower2Candidate](IdentityNo from, IdentityNo &to) mutable {
		if (from == FollowerNo && to == CandidateNo)
			++follower2Candidate;
	};
	p[0]->StartUp();
//	sleep(1);
//	p[0]->Pause();
//	sleep(2);
//	p[0]->Resume();
	sleep(10);
	p[0]->ShutDown();
	printf("initialize one server, transform from follower to candidate for %d time\n", (int) follower2Candidate);
}

/// this test case create one instance of server and send empty heartbeat periodically.
/// follower should never transform to candidate.
void Follower_AppendEntry() {
	IdentityTestHelper helper;
	auto srvs = helper.makeServers(1);
	srvs.front()->Init();
	auto &debugContext = srvs[0]->GetCtx();
	std::atomic<int> F2C{0};
	std::atomic<int> C2L{0};
	debugContext.before_tranform = [&](IdentityNo from, IdentityNo &to) mutable {
		if (from == FollowerNo && to == CandidateNo)
			F2C++;
		else if (from == CandidateNo && to == LeaderNo)
			C2L++;
	};

	srvs.front()->StartUp();
	const auto timeout = srvs.front()->GetInfo().get_electionTimeout() / 2;
	auto id = srvs.front()->GetInfo().get_local();

	std::vector<std::unique_ptr<RaftPeerClientImpl> > vClient;

	boost::thread th1([&]() mutable {
		sleep(1);
		srvs.front()->Pause();
		sleep(2);
		srvs.front()->Resume();
	});
	for (int i = 0, appendTime = 100; i < appendTime; ++i) {
		vClient.push_back(std::make_unique<RaftPeerClientImpl>(id));

		vClient.back()->th = boost::thread([&vClient]() mutable {
			grpc::ClientContext ctx;
			PbAppendEntriesRequest msg;
			PbAppendEntriesResponse rsp;
			msg.set_term(100);
			msg.set_prevlogterm(-1);
			msg.set_prevlogindex(0);

			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(30));
			grpc::Status status = vClient.back()->stub_->AppendEntriesRPC(&ctx, msg, &rsp);
			printf("rpc sent\n");
			printf("%lld\n", rsp.term());
			if (status.ok()) printf("msg is OK!\n");
			else {
				printf("msg is error\n");
				printf("msg: %d %s\n", status.error_code(), status.error_message().c_str());
			}
		});
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
	}
	srvs.front()->ShutDown();
	assert(F2C == 0);
	printf("create one follower, and send heartbeat to it manually, it remains follower\n");
}

void Candidate_Basic() {
	IdentityTestHelper helper;
	const std::size_t SrvNum = 1;
	auto srvs = helper.makeServers(SrvNum);
	srvs[0]->Init();
	auto &ctx = srvs[0]->GetCtx();
	ctx.before_tranform = [](IdentityNo from, IdentityNo &to) mutable {
		if (from == FollowerNo) throw std::runtime_error("unexpected test");
		if (from != DownNo && to != CandidateNo) throw std::runtime_error("transform not to candidate");
		to = to == DownNo ? DownNo : CandidateNo;
	};
	srvs[0]->StartUp();
	sleep(100);
	srvs[0]->ShutDown();
}

/**
 * This test creates three server instances, it shows they can always pick out one leader.
 * And the other two remain followers because of the leader's suppressing heartbeats.
 * */
void CandidateNaive() {
	IdentityTestHelper helper;
	const std::size_t SrvNum = 2;
	auto srvs = helper.makeServers(SrvNum);
	const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();
	std::atomic<int> candidate2Follower{0}, candidate2Leader{0};

	for (auto &srv : srvs) {
		srv->Init();
		RaftDebugContext &ctx = srv->GetCtx();

		ctx.before_tranform = ([&](IdentityNo from, IdentityNo &to) mutable {
			if (from == CandidateNo && to == LeaderNo) {
				printf("server %s transform from candidate to leader\n", srv->GetInfo().get_local().toString().c_str());
				++candidate2Leader;
			} else if (from == CandidateNo && to == FollowerNo) {
				++candidate2Follower;
				to = DownNo;
			} else if (from == CandidateNo && to == CandidateNo)
				to = CandidateNo;
		});
		srv->StartUp();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(ElectionTimeout * 8));
	for (auto &srv : srvs)
		srv->ShutDown();

	printf("%d, %d\n", (int) candidate2Leader, (int) candidate2Follower);
	printf(
			"three servers init to be follower, then one leader is elected. No other followers transform to be cnadidate\n");
}

/**
 * This test creates one instance of follower, I have no idea what it is about.
 * */
void PutBasic() {
	IdentityTestHelper helper;
	const std::size_t SrvNum = 1;
	auto srvs = helper.makeServers(SrvNum);
//	const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();

	auto &srv = srvs.front();
	auto id = srvs.front()->GetInfo().get_local();
	srv->Init();
	srv->StartUp();
	std::unique_ptr<RaftPeerClientImpl> client;
	client = std::make_unique<RaftPeerClientImpl>(id);

	for (int i = 0; i < 10; ++i) {
		client->th = boost::thread([&client, i]() mutable {
			grpc::ClientContext ctx;
			PbClientRequest msg;
			PbClientResponse rsp;
			std::string str_key = "shit";
			std::string str_val = "dick";
			str_key += char('0' + i);
			str_val += char('0' + i);
			msg.set_key(str_key);
			msg.set_val(str_val);
			msg.set_command("Put");
			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(100));
			grpc::Status status = client->stub_->ClientRPC(&ctx, msg, &rsp);
			printf("rpc sent\n");
			if (status.ok()) printf("msg is OK!\n");
			else {
				printf("msg is error\n");
				printf("msg: %d %s\n", status.error_code(), status.error_message().c_str());
			}
		});
		client->th.join();
	}
	srv->ShutDown();
	printf("put method all fails because of one single follower, this situation is strange.\n");
}

/**
 * This test creates two instances of server. By manually sending put request to the leader server, leader can
 * help follower server increment its log, and increment commit index. After doing that, it applies committed log
 * entry to the data map.
 * */
/**
 * 测试显示我在关机的时候会翻车
 * */
void PutLeaderDirectly() {
	IdentityTestHelper helper;
	const std::size_t SrvNum = 2;
	auto srvs = helper.makeServers(SrvNum);
//	const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();

	auto &srv = srvs.front();
	auto &srv2 = srvs.back();

	srv->Init();
	srv2->Init();
	RaftDebugContext &context = srv->GetCtx();
	std::atomic<int> candidate2Leader{0};

	context.before_tranform = ([&](IdentityNo from, IdentityNo &to) mutable {
		if (to == FollowerNo) {
			to = LeaderNo;
			++candidate2Leader;
		}
	});

	srv->StartUp();
	srv2->StartUp();
	while (candidate2Leader != 1);

	auto id = srvs.front()->GetInfo().get_local();
	std::unique_ptr<RaftPeerClientImpl> client;
	client = std::make_unique<RaftPeerClientImpl>(id);

	for (int i = 0; i < 10; ++i) {
		client->th = boost::thread([&client, i]() mutable {
			grpc::ClientContext ctx;
			PbClientRequest msg;
			PbClientResponse rsp;
			std::string str_key = "shit";
			std::string str_val = "dick";
			str_key += char('0' + i);
			str_val += char('0' + i);
			msg.set_key(str_key);
			msg.set_val(str_val);
			msg.set_command("Put");

			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(100));
			grpc::Status status = client->stub_->ClientRPC(&ctx, msg, &rsp);
			printf("rpc sent\n");
			if (status.ok()) printf("msg is OK!\n");
			else {
				printf("msg is error\n");
				printf("msg: %d %s\n", status.error_code(), status.error_message().c_str());
			}
		});
		client->th.join();

//		fprintf(stderr, "%d time request, traverse map: ", i);
//		auto data = srv->GetKV();
//		for (auto elem : data) {
//			fprintf(stderr, "%s - %s; ", elem.first.c_str(), elem.second.c_str());
//		}
//		fprintf(stderr, "\n");
		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	}
	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	auto m = srv->GetKV();
	for (auto elem : m) {
		std::cout << elem.first << ' ' << elem.second << std::endl;
	}
	m = srv2->GetKV();
	for (auto elem : m) {
		std::cout << elem.first << ' ' << elem.second << std::endl;
	}
	printf("after sending put request for ten times, leader and follower's log size: %zu %zu, leader's commitIndex %lld, "
				 "follower's commitIndex %lld\n",
				 srv->GetState().log.length(), srv2->GetState().log.length(), srv->GetState().commitIndex,
				 srv2->GetState().commitIndex);
	srv->ShutDown();
	srv2->ShutDown();
	client->th.join();
	printf("Put method success because of one single leader.\n");
	printf("test whether a follower's log can be updated by heartbeat\n");
	printf("a follower can add to its log by leader's heartbeat, but synchronization isn't guaranteed\n");
	printf("all put KV pairs are safely applied. \n");
}

void PutBroadcastFromFollower() {
	IdentityTestHelper helper;
	const std::size_t SrvNum = 2;
	auto srvs = helper.makeServers(SrvNum);
//	const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();

	auto &srv = srvs.front();
	auto &srv2 = srvs.back();

	srv->Init();
	srv2->Init();
	RaftDebugContext &context = srv->GetCtx();
	std::atomic<int> candidate2Leader{0};

	context.before_tranform = ([&](IdentityNo from, IdentityNo &to) mutable {
		if (to == FollowerNo) {
			to = LeaderNo;
			++candidate2Leader;
		}
	});

	srv->StartUp();
	srv2->StartUp();
	while (candidate2Leader != 1);

	auto id = srvs.back()->GetInfo().get_local();
	std::unique_ptr<RaftPeerClientImpl> client;
	client = std::make_unique<RaftPeerClientImpl>(id);

	for (int i = 0; i < 10; ++i) {
		client->th = boost::thread([&client, i]() mutable {
			grpc::ClientContext ctx;
			PbClientRequest msg;
			PbClientResponse rsp;
			std::string str_key = "shit";
			std::string str_val = "dick";
			str_key += char('0' + i);
			str_val += char('0' + i);
			msg.set_key(str_key);
			msg.set_val(str_val);
			msg.set_command("Put");

			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(100));
			grpc::Status status = client->stub_->ClientRPC(&ctx, msg, &rsp);
			printf("rpc sent\n");
			if (status.ok()) printf("msg is OK!\n");
			else {
				printf("msg is error\n");
				printf("msg: %d %s\n", status.error_code(), status.error_message().c_str());
			}
		});
		client->th.join();

		fprintf(stderr, "%d time request, traverse map: ", i);
		auto data = srv->GetKV();
		for (auto elem : data) {
			fprintf(stderr, "%s - %s; ", elem.first.c_str(), elem.second.c_str());
		}
		fprintf(stderr, "\n");
		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));

	}
	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));

	auto m = srv->GetKV();
	for (auto elem : m) {
		std::cout << elem.first << ' ' << elem.second << std::endl;
	}
	m = srv2->GetKV();
	for (auto elem : m) {
		std::cout << elem.first << ' ' << elem.second << std::endl;
	}
	printf("after sending put request for ten times, leader and follower's log size: %zu %zu, leader's commitIndex %lld, "
				 "follower's commitIndex %lld\n",
				 srv->GetState().log.length(), srv2->GetState().log.length(), srv->GetState().commitIndex,
				 srv2->GetState().commitIndex);
	srv->ShutDown();
	srv2->ShutDown();
	client->th.join();
	printf("Put method success because of one single leader.\n");
	printf("test whether a follower's log can be updated by heartbeat\n");
	printf("a follower can add to its log by leader's heartbeat, but synchronization isn't guaranteed\n");
}

/**
 * This test send put request directly to leader, and leader uses promise and future trick to reply.
 * */
void PutLeaderAsync() {
	IdentityTestHelper helper;
	const std::size_t SrvNum = 2;
	auto srvs = helper.makeServers(SrvNum);
//	const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();

	auto &srv = srvs.front();
	auto &srv2 = srvs.back();

	srv->Init();
	srv2->Init();
	RaftDebugContext &context = srv->GetCtx();
	std::atomic<int> candidate2Leader{0};

	context.before_tranform = ([&](IdentityNo from, IdentityNo &to) mutable {
		if (to == FollowerNo) {
			to = LeaderNo;
			++candidate2Leader;
		}
	});

	srv->StartUp();
	srv2->StartUp();
	while (candidate2Leader != 1);

	auto id = srvs.front()->GetInfo().get_local();
	std::unique_ptr<RaftPeerClientImpl> client;
	client = std::make_unique<RaftPeerClientImpl>(id);

	for (int i = 0; i < 10; ++i) {
		client->th = boost::thread([&client, i]() mutable {
			grpc::ClientContext ctx;
			PbClientRequest msg;
			PbClientResponse rsp;
			std::string str_key = "shit";
			std::string str_val = "dick";
			str_key += char('0' + i);
			str_val += char('0' + i);
			msg.set_key(str_key);
			msg.set_val(str_val);
			msg.set_command("Put");

			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(1000));
			grpc::Status status = client->stub_->ClientRPC(&ctx, msg, &rsp);
			printf("rpc sent\n");
			if (status.ok()) printf("msg is OK! %s\n", rsp.replymsg().c_str());
			else {
				printf("msg is error\n");
				printf("msg: %d %s\n", status.error_code(), status.error_message().c_str());
			}
		});
		client->th.join();

//		fprintf(stderr, "%d time request, traverse map: ", i);
//		auto data = srv->GetKV();
//		for (auto elem : data) {
//			fprintf(stderr, "%s - %s; ", elem.first.c_str(), elem.second.c_str());
//		}
//		fprintf(stderr, "\n");
		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	}
	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	auto m = srv->GetKV();
	for (auto elem : m) {
		std::cout << elem.first << ' ' << elem.second << std::endl;
	}
	m = srv2->GetKV();
	for (auto elem : m) {
		std::cout << elem.first << ' ' << elem.second << std::endl;
	}
	printf("after sending put request for ten times, leader and follower's log size: %zu %zu, leader's commitIndex %lld, "
				 "follower's commitIndex %lld\n",
				 srv->GetState().log.length(), srv2->GetState().log.length(), srv->GetState().commitIndex,
				 srv2->GetState().commitIndex);
	srv->ShutDown();
	srv2->ShutDown();
	client->th.join();
	printf("put method is OK, all put msg sends to the leader is safely returned.\n");
}

/**
 * This test send put method to follower.
 * */
void PutFollowerAsync() {
	IdentityTestHelper helper;
	const std::size_t SrvNum = 3;
	auto srvs = helper.makeServers(SrvNum);
//	const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();

	for(auto &per_srv : srvs) {
		per_srv->Init();
	}

	auto &srv = srvs.front();
	auto &srv2 = srvs.back();


	RaftDebugContext &context = srv->GetCtx();
	std::atomic<int> candidate2Leader{0};

	context.before_tranform = ([&](IdentityNo from, IdentityNo &to) mutable {
		if (to == FollowerNo) {
			to = LeaderNo;
			++candidate2Leader;
		}
	});

	for(auto &per_srv : srvs) {
		per_srv->StartUp();
	}
	while (candidate2Leader != 1);

	auto id = srvs.back()->GetInfo().get_local();
	std::unique_ptr<RaftPeerClientImpl> client;
	client = std::make_unique<RaftPeerClientImpl>(id);

	for (int i = 0; i < 10; ++i) {
		client->th = boost::thread([&client, i]() mutable {
			grpc::ClientContext ctx;
			PbClientRequest msg;
			PbClientResponse rsp;
			std::string str_key = "shit";
			std::string str_val = "dick";
			str_key += char('0' + i);
			str_val += char('0' + i);
			msg.set_key(str_key);
			msg.set_val(str_val);
			msg.set_command("Put");

			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(1000));
			grpc::Status status = client->stub_->ClientRPC(&ctx, msg, &rsp);
			printf("rpc sent\n");
			if (status.ok()) printf("msg is OK! %s\n", rsp.replymsg().c_str());
			else {
				printf("msg is error\n");
				printf("msg: %d %s\n", status.error_code(), status.error_message().c_str());
			}
		});
		client->th.join();

//		fprintf(stderr, "%d time request, traverse map: ", i);
//		auto data = srv->GetKV();
//		for (auto elem : data) {
//			fprintf(stderr, "%s - %s; ", elem.first.c_str(), elem.second.c_str());
//		}
//		fprintf(stderr, "\n");
		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	}
	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));

	for(auto &per_srv : srvs) {
		auto m = per_srv->GetKV();
		for (auto elem : m) {
			std::cout << elem.first << ' ' << elem.second << std::endl;
		}
	}

	printf("after sending put request for ten times, leader and follower's log size: %zu %zu, leader's commitIndex %lld, "
				 "follower's commitIndex %lld\n",
				 srv->GetState().log.length(), srv2->GetState().log.length(), srv->GetState().commitIndex,
				 srv2->GetState().commitIndex);
	for(auto &per_srv : srvs) {
		printf("log size: %zu commit index: %lld\n", per_srv->GetState().log.length(), per_srv->GetState().commitIndex);
		per_srv->ShutDown();
	}
	client->th.join();
	printf("put method is OK, all put msg sends to the leader is safely returned.\n");
}

/**
 * This test send put request randomly to each server in the whole cluster.
 * */
void PutComprehensiveAsync() {
	IdentityTestHelper helper;
	const std::size_t SrvNum = 3;
	auto srvs = helper.makeServers(SrvNum);
//	const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();

	for (auto &per_srv : srvs) {
		per_srv->Init();
	}

	auto &srv = srvs.front();
	auto &srv2 = srvs.back();


	RaftDebugContext &context = srv->GetCtx();
	std::atomic<int> candidate2Leader{0};

	context.before_tranform = ([&](IdentityNo from, IdentityNo &to) mutable {
		if (to == FollowerNo) {
			to = LeaderNo;
			++candidate2Leader;
		}
	});

	for (auto &per_srv : srvs) {
		per_srv->StartUp();
	}
	while (candidate2Leader != 1);

	std::vector<std::unique_ptr<RaftPeerClientImpl> > clients;
	for (auto &per_srv : srvs) {
		clients.push_back(std::make_unique<RaftPeerClientImpl> (per_srv->GetInfo().get_local()));
	}

	for (int i = 0; i < 10; ++i) {
		/// randomly choose one client to send.
		int send_to = rand() % clients.size();
		auto &client = clients[send_to];
		client->th = boost::thread([&client, i]() mutable {
			grpc::ClientContext ctx;
			PbClientRequest msg;
			PbClientResponse rsp;
			std::string str_key = "shit";
			std::string str_val = "dick";
			str_key += char('0' + i);
			str_val += char('0' + i);
			msg.set_key(str_key);
			msg.set_val(str_val);
			msg.set_command("Put");

			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(1000));
			grpc::Status status = client->stub_->ClientRPC(&ctx, msg, &rsp);
			printf("rpc sent\n");
			if (status.ok()) printf("msg is OK! %s\n", rsp.replymsg().c_str());
			else {
				printf("msg is error\n");
				printf("msg: %d %s\n", status.error_code(), status.error_message().c_str());
			}
		});
		client->th.join();

//		fprintf(stderr, "%d time request, traverse map: ", i);
//		auto data = srv->GetKV();
//		for (auto elem : data) {
//			fprintf(stderr, "%s - %s; ", elem.first.c_str(), elem.second.c_str());
//		}
//		fprintf(stderr, "\n");
		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	}
	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));

	for (auto &per_srv : srvs) {
		auto m = per_srv->GetKV();
		for (auto elem : m) {
			std::cout << elem.first << ' ' << elem.second << std::endl;
		}
	}

	printf("after sending put request for ten times, leader and follower's log size: %zu %zu, leader's commitIndex %lld, "
				 "follower's commitIndex %lld\n",
				 srv->GetState().log.length(), srv2->GetState().log.length(), srv->GetState().commitIndex,
				 srv2->GetState().commitIndex);
	for (auto &per_srv : srvs) {
		printf("log size: %zu commit index: %lld\n", per_srv->GetState().log.length(), per_srv->GetState().commitIndex);
		per_srv->ShutDown();
	}
//	client->th.join();
	printf("put method is OK, all put msg sends to the leader is safely returned.\n");
}

/**
 * This test send put request randomly to each server in the whole cluster.
 * And it shuts down one server at a time randomly.
 * */
void ShutDownNonLeaderComprehensiveAsync() {
	IdentityTestHelper helper;
	const std::size_t SrvNum = 3;
	auto srvs = helper.makeServers(SrvNum);
//	const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();

	for (auto &per_srv : srvs) {
		per_srv->Init();
	}

	auto &srv = srvs.front();

	RaftDebugContext &context = srv->GetCtx();
	std::atomic<int> candidate2Leader{0};

	context.before_tranform = ([&](IdentityNo from, IdentityNo &to) mutable {
		if (to == FollowerNo) {
			to = LeaderNo;
			++candidate2Leader;
		}
	});

	for (auto &per_srv : srvs) {
		per_srv->StartUp();
	}
	while (candidate2Leader != 1);

	std::vector<std::unique_ptr<RaftPeerClientImpl> > clients;
	for (auto &per_srv : srvs) {
		clients.push_back(std::make_unique<RaftPeerClientImpl>(per_srv->GetInfo().get_local()));
	}

	boost::atomic<bool> down[SrvNum];
	boost::thread th_down([&]() mutable {
		for (int i = 0; i < 3; ++i) {
			sleep(1);
			boost::this_thread::interruption_point();
			int d = rand() % 2 + 1;
//			int d = rand() % 3;
			down[d] = true;
			srvs[d]->Pause();
			sleep(2);
			down[d] = false;
			srvs[d]->Resume();
		}
	});

	for (int i = 0; i < 10; ++i) {
		/// randomly choose one client to send.
		int send_to;
		while (true) {
			send_to = rand() % clients.size();
			if (down[send_to]) continue;
			break;
		}
		auto &client = clients[send_to];
		client->th = boost::thread([&client, i]() mutable {
			grpc::ClientContext ctx;
			PbClientRequest msg;
			PbClientResponse rsp;
			std::string str_key = "shit";
			std::string str_val = "dick";
			str_key += char('0' + i);
			str_val += char('0' + i);
			msg.set_key(str_key);
			msg.set_val(str_val);
			msg.set_command("Put");

			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(500));
			fprintf(stderr, "message sent to server %s\n", client->id.toString().c_str());
			grpc::Status status = client->stub_->ClientRPC(&ctx, msg, &rsp);
			printf("rpc sent\n");
			if (status.ok()) printf("msg is OK! %s\n", rsp.replymsg().c_str());
			else {
				printf("msg is error\n");
				printf("msg: %d %s\n", status.error_code(), status.error_message().c_str());
			}
		});
		client->th.join();

//		fprintf(stderr, "%d time request, traverse map: ", i);
//		auto data = srv->GetKV();
//		for (auto elem : data) {
//			fprintf(stderr, "%s - %s; ", elem.first.c_str(), elem.second.c_str());
//		}
//		fprintf(stderr, "\n");
		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	}
	th_down.interrupt();
	th_down.join();

	boost::this_thread::sleep_for(boost::chrono::milliseconds(5000));

	for (auto &per_srv : srvs) {
		auto m = per_srv->GetKV();
		for (auto elem : m) {
			std::cout << elem.first << ' ' << elem.second << std::endl;
		}
	}

//	printf("after sending put request for ten times, leader and follower's log size: %zu %zu, leader's commitIndex %lld, "
//				 "follower's commitIndex %lld\n",
//				 srv->GetState().log.length(), srv2->GetState().log.length(), srv->GetState().commitIndex,
//				 srv2->GetState().commitIndex);
	for (auto &per_srv : srvs) {
		printf("log size: %zu commit index: %lld\n", per_srv->GetState().log.length(), per_srv->GetState().commitIndex);
		per_srv->ShutDown();
	}
//	client->th.join();
	printf("put method is OK, all put msg sends to the leader is safely returned.\n");
}

void ShutDownComprehensiveAsync() {
	IdentityTestHelper helper;
	const std::size_t SrvNum = 3;
	auto srvs = helper.makeServers(SrvNum);
//	const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();

	for (auto &per_srv : srvs) {
		per_srv->Init();
	}


	for (auto &per_srv : srvs) {
		per_srv->StartUp();
	}
	sleep(1);

	std::vector<std::unique_ptr<RaftPeerClientImpl> > clients;
	for (auto &per_srv : srvs) {
		clients.push_back(std::make_unique<RaftPeerClientImpl>(per_srv->GetInfo().get_local()));
	}

	boost::atomic<bool> down[SrvNum];
	boost::thread th_down([&]() mutable {
		for (int i = 0; i < 3; ++i) {
			sleep(1);
			boost::this_thread::interruption_point();
//			int d = rand() % 2 + 1;
			int d = rand() % 3;
			down[d] = true;
			srvs[d]->Pause();
			sleep(2);
			down[d] = false;
			srvs[d]->Resume();
		}
	});

	for (int i = 0; i < 10; ++i) {
		/// randomly choose one client to send.
		int send_to;
		while (true) {
			send_to = rand() % clients.size();
			if (down[send_to]) continue;
			break;
		}
		auto &client = clients[send_to];
		client->th = boost::thread([&client, i]() mutable {
			grpc::ClientContext ctx;
			PbClientRequest msg;
			PbClientResponse rsp;
			std::string str_key = "shit";
			std::string str_val = "dick";
			str_key += char('0' + i);
			str_val += char('0' + i);
			msg.set_key(str_key);
			msg.set_val(str_val);
			msg.set_command("Put");

			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(500));
			fprintf(stderr, "message sent to server %s\n", client->id.toString().c_str());
			grpc::Status status = client->stub_->ClientRPC(&ctx, msg, &rsp);
			printf("rpc sent\n");
			if (status.ok()) printf("msg is OK! %s\n", rsp.replymsg().c_str());
			else {
				printf("msg is error\n");
				printf("msg: %d %s\n", status.error_code(), status.error_message().c_str());
			}
		});
		client->th.join();

//		fprintf(stderr, "%d time request, traverse map: ", i);
//		auto data = srv->GetKV();
//		for (auto elem : data) {
//			fprintf(stderr, "%s - %s; ", elem.first.c_str(), elem.second.c_str());
//		}
//		fprintf(stderr, "\n");
		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	}
	th_down.interrupt();
	th_down.join();

	boost::this_thread::sleep_for(boost::chrono::milliseconds(5000));

	for (auto &per_srv : srvs) {
		auto m = per_srv->GetKV();
		for (auto elem : m) {
			std::cout << elem.first << ' ' << elem.second << std::endl;
		}
	}

//	printf("after sending put request for ten times, leader and follower's log size: %zu %zu, leader's commitIndex %lld, "
//				 "follower's commitIndex %lld\n",
//				 srv->GetState().log.length(), srv2->GetState().log.length(), srv->GetState().commitIndex,
//				 srv2->GetState().commitIndex);
	for (auto &per_srv : srvs) {
		printf("log size: %zu commit index: %lld\n", per_srv->GetState().log.length(), per_srv->GetState().commitIndex);
		per_srv->ShutDown();
	}
//	client->th.join();
	printf("put method is OK, all put msg sends to the leader is safely returned.\n");
}


/**
 *
 * */
void finalTest() {
	IdentityTestHelper helper;
	const std::size_t SrvNum = 3;
	auto srvs = helper.makeServers(SrvNum);
//	const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();

	for (auto &per_srv : srvs) {
		per_srv->Init();
	}

	for (auto &per_srv : srvs) {
		per_srv->StartUp();
	}
	sleep(1);

	std::vector<std::unique_ptr<RaftPeerClientImpl> > clients;
	for (auto &per_srv : srvs) {
		clients.push_back(std::make_unique<RaftPeerClientImpl>(per_srv->GetInfo().get_local()));
	}

	boost::atomic<bool> down[SrvNum];
	memset(down, false, sizeof(down));

	boost::thread th_down([&]() mutable {
		for (int i = 0; i < 3; ++i) {
			boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
			boost::this_thread::interruption_point();
//			int d = rand() % 2 + 1;
			int d = rand() % 3;
			down[d] = true;
			srvs[d]->Pause();
			boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));
			down[d] = false;
			srvs[d]->Resume();
		}
	});

	for (int i = 0; i < 100; ++i) {
		/// randomly choose one client to send.
		int send_to;
		while (true) {
			send_to = rand() % clients.size();
			if (down[send_to]) continue;
			break;
		}
		auto &client = clients[send_to];
		client->th = boost::thread([&client, i]() mutable {
			grpc::ClientContext ctx;
			PbClientRequest msg;
			PbClientResponse rsp;
			std::string str_key = "shit";
			std::string str_val = "dick";
			std::string number = "";
			msg.set_command("Put");
			while (i) {
				number.insert(number.begin(), char('0' + i % 10));
				i /= 10;
			}
			str_key += number;
			str_val += number;
			msg.set_key(str_key);
			msg.set_val(str_val);

			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(500));
			fprintf(stderr, "message sent to server %s\n", client->id.toString().c_str());
			grpc::Status status = client->stub_->ClientRPC(&ctx, msg, &rsp);
			printf("rpc sent\n");
			if (status.ok()) printf("msg is OK! %s\n", rsp.replymsg().c_str());
			else {
				printf("msg is error\n");
				printf("msg: %d %s\n", status.error_code(), status.error_message().c_str());
			}
		});
		client->th.join();

//		fprintf(stderr, "%d time request, traverse map: ", i);
//		auto data = srv->GetKV();
//		for (auto elem : data) {
//			fprintf(stderr, "%s - %s; ", elem.first.c_str(), elem.second.c_str());
//		}
//		fprintf(stderr, "\n");
		boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	}
	th_down.interrupt();
	th_down.join();

	boost::this_thread::sleep_for(boost::chrono::milliseconds(2000));

	for (auto &per_srv : srvs) {
		auto m = per_srv->GetKV();
		for (auto elem : m) {
			std::cout << elem.first << ' ' << elem.second << std::endl;
		}
	}

//	printf("after sending put request for ten times, leader and follower's log size: %zu %zu, leader's commitIndex %lld, "
//				 "follower's commitIndex %lld\n",
//				 srv->GetState().log.length(), srv2->GetState().log.length(), srv->GetState().commitIndex,
//				 srv2->GetState().commitIndex);
	for (auto &per_srv : srvs) {
		printf("log size: %zu commit index: %lld\n", per_srv->GetState().log.length(), per_srv->GetState().commitIndex);
		per_srv->ShutDown();
	}
//	client->th.join();
	printf("put method is OK, all put msg sends to the leader is safely returned.\n");
}

void Test1() {
	IdentityTestHelper helper;
	auto p = helper.makeServers(3);

	std::atomic<int> follower2Candidate{0}, candidate2Leader{0};

	for (auto &srv : p) {
		srv->Init();
		RaftDebugContext &debugContext = srv->GetCtx();
		debugContext.before_tranform = [&follower2Candidate, &candidate2Leader](IdentityNo from, IdentityNo &to) mutable {
			if (from == FollowerNo && to == CandidateNo)
				++follower2Candidate;
			if (from == CandidateNo && to == LeaderNo)
				++candidate2Leader;
		};
	}

	for (auto &srv : p) {
		srv->StartUp();
	}
	sleep(10);
	for (auto &srv : p) {
		srv->ShutDown();
	}
	printf("begin with 3 servers, follower2Candidate: %d, candidate2Leader %d\n", (int) follower2Candidate,
				 (int) candidate2Leader);
}

void Test2() {
	IdentityTestHelper helper;
	const std::size_t SrvNum = 3;
	auto srvs = helper.makeServers(SrvNum);

	for (auto &per_srv : srvs) {
		per_srv->Init();
	}

	std::cout << "Test Put method..." << std::endl;

	for (auto &per_srv : srvs) {
		per_srv->StartUp();
	}
	sleep(1);

	std::vector<std::unique_ptr<RaftPeerClientImpl> > clients;
	for (auto &per_srv : srvs) {
		clients.push_back(std::make_unique<RaftPeerClientImpl>(per_srv->GetInfo().get_local()));
	}

	boost::atomic<bool> down[SrvNum];
	memset(down, false, sizeof(down));

	boost::thread th_down([&]() mutable {
		for (int i = 0; i < 3; ++i) {
			boost::this_thread::disable_interruption di;
			boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
			int d = 0;
			while (true) {
				if (srvs[d]->GetState().currentIdentity != 2) d = (d + 1) % 3;
				else break;
			}
			down[d] = true;
			srvs[d]->Pause();
			boost::this_thread::sleep_for(boost::chrono::milliseconds(4000));
			down[d] = false;
			srvs[d]->Resume();
			{
				boost::this_thread::restore_interruption ri(di);
				boost::this_thread::interruption_point();
			}
		}
	});

	for (int i = 0; i < 20; ++i) {
		/// randomly choose one client to send.
		int send_to;
		while (true) {
			send_to = rand() % clients.size();
			if (down[send_to]) continue;
			break;
		}
		auto &client = clients[send_to];
		client->th.join();
		client->th = boost::thread([&client, i]() mutable {
			/// make key and value
			grpc::ClientContext ctx;
			PbClientRequest msg;
			PbClientResponse rsp;
			std::string str_key = "key";
			std::string str_val = "value";
			std::string number = "";
			msg.set_command("Put");
			int num = i;
			while (num) {
				number.insert(number.begin(), char('0' + num % 10));
				num /= 10;
			}
			str_key += number;
			str_val += number;
			msg.set_key(str_key);
			msg.set_val(str_val);

			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(5000));
			std::cerr << "request message " << i << ": " + msg.key() + " " + msg.val() + " sent" << std::endl;
			grpc::Status status = client->stub_->ClientRPC(&ctx, msg, &rsp);
			if (status.ok()) {
				std::cout << "request message " << i << ": " + msg.key() + " " + msg.val() + ", reply: " << rsp.replymsg()
									<< std::endl;
			} else {
				std::cout << status.error_code() << " " << status.error_message() << std::endl;
			}
		});
		client->th.join();
		boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	}
	th_down.interrupt();
	th_down.join();

	sleep(5);
	for (auto &per_srv : srvs) {
		auto m = per_srv->GetKV();
		std::cout << "KV map for server: " << per_srv->GetInfo().get_local().toString() << std::endl;
		for (auto elem : m) {
			std::cout << elem.first << ' ' << elem.second << std::endl;
		}
	}

	std::cout << "Test Get method..." << std::endl;
	for (int i = 0; i < 20; ++i) {
		/// randomly choose one client to send.
		int send_to;
		while (true) {
			send_to = rand() % clients.size();
			if (down[send_to]) continue;
			break;
		}
		auto &client = clients[send_to];
		client->th.join();
		client->th = boost::thread([&client, i]() mutable {
			/// make key and value
			grpc::ClientContext ctx;
			PbClientRequest msg;
			PbClientResponse rsp;
			std::string str_key = "key";
			std::string str_val = "value";
			std::string number = "";
			msg.set_command("Get");
			int num = i;
			while (num) {
				number.insert(number.begin(), char('0' + num % 10));
				num /= 10;
			}
			str_key += number;
			str_val += number;
			msg.set_key(str_key);
			msg.set_val(str_val);

			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(500));
			std::cerr << "request message " << i << ": " + msg.key() + " " + msg.val() + " sent" << std::endl;
			grpc::Status status = client->stub_->ClientRPC(&ctx, msg, &rsp);
			if (status.ok()) {
				std::cerr << "request message " << i << ": " + msg.key() + " " + msg.val() + ", reply: " << rsp.replymsg()
									<< std::endl;
			} else {
				std::cerr << status.error_code() << " " << status.error_message() << std::endl;
			}
		});
		boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	}
	for (auto &per_srv : srvs) {
		printf("log size: %zu commit index: %lld\n", per_srv->GetState().log.length(), per_srv->GetState().commitIndex);
		per_srv->ShutDown();
	}
}
};

using namespace SJTU;

int main() {
//	SJTU::Test1();
//	SJTU::Test2();

//	SJTU::finalTest();
//	SJTU::ShutDownComprehensiveAsync();
//	SJTU::ShutDownNonLeaderComprehensiveAsync();
//	SJTU::PutComprehensiveAsync();
//	SJTU::PutFollowerAsync();
//	SJTU::PutLeaderAsync();
//	SJTU::PutBroadcastFromFollower();
//	SJTU::PutLeaderDirectly();
//	SJTU::PutBasic();
//	SJTU::Follower_Basic();
//	SJTU::Follower_AppendEntry();
//	SJTU::Candidate_Basic();
//	SJTU::CandidateNaive();
	return 0;
}
