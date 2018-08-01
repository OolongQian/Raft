#include "IdentityTestHelper.h"
#include "../../../include/raft/raft_proto/raft_server.h"
#include "../../../src/raft/raft.cpp"
#include "../../../include/my_server.h"

namespace SJTU {


	/// 看看能不能变身
	void Follower_Basic() {
		printf("Follower_basic test...\n");
		IdentityTestHelper helper;
		auto &debugContext = Raft::GetDebug();
		std::atomic<int> follower2Candidate{0};
		debugContext.before_tranform = [&follower2Candidate](IdentityNo from, IdentityNo to) {
			if (from == FollowerNo && to == CandidateNo)
				++follower2Candidate;
		};
		auto p = helper.makeServers(1);
		p[0]->Init();
		p[0]->StartUp();
		sleep(10);
		p[0]->ShutDown();
		printf("initialize one server, transform from follower to candidate for %d time\n", (int) follower2Candidate);
	}

	/// this test case create one instance of server and send empty heartbeat periodically.
	/// follower should never transform to candidate.
	void Follower_AppendEntry() {
		IdentityTestHelper helper;
		auto srvs = helper.makeServers(1);

		auto &debugContext = Raft::GetDebug();
		std::atomic<int> F2C{0};
		std::atomic<int> C2L{0};
		debugContext.before_tranform = [&](IdentityNo from, IdentityNo to) {
			if (from == FollowerNo && to == CandidateNo)
				F2C++;
			else if (from == CandidateNo && to == LeaderNo)
				C2L++;
		};

		srvs.front()->Init();
		srvs.front()->StartUp();
		const auto timeout = srvs.front()->GetInfo().get_electionTimeout() / 2;
		auto id = srvs.front()->GetInfo().get_local();

		std::vector<std::unique_ptr<RaftPeerClientImpl> > vClient;
		for (int i = 0, appendTime = 10; i < appendTime; ++i) {
			vClient.push_back(std::make_unique<RaftPeerClientImpl>(id));

			vClient.back()->th = boost::thread([&vClient]() mutable {
				grpc::ClientContext ctx;
				PbAppendEntriesRequest msg;
				PbAppendEntriesResponse rsp;
				msg.set_term(0);

				ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(300));
				grpc::Status status = vClient.back()->stub_->AppendEntriesRPC(&ctx, msg, &rsp);
				printf("rpc sent\n");
				printf("%lld\n", rsp.term());
				if (status.ok()) printf("msg is OK!\n");
				else printf("msg is error\n");
			});
			std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		}
		sleep(10);
		printf("%d %d\n", (int) F2C, (int) C2L);
		srvs.front()->ShutDown();
	}
};


using namespace SJTU;

int main() {
//	SJTU::Follower_Basic();
	SJTU::Follower_AppendEntry();
//	IdentityTestHelper helper;

//	auto p = helper.makeServers(1);
//	const ServerId &id = p[0]->GetInfo().get_local();

//	myServer server("127.0.0.1:50000");


//	myServer::Foo service;
//	grpc::ServerBuilder builder;
//	builder.AddListeningPort(id.toString(), grpc::InsecureServerCredentials());
//	builder.RegisterService(&service);
//	auto server = builder.BuildAndStart();
//	boost::thread th([&] {
//		std::cout << "Server listening on " << id.toString() << std::endl;
//		server->Wait();
//		});

//		p[0]->Init();
//		p[0]->StartUp();
//
//		sleep(1);
//	const auto timeout = p[0]->GetInfo().get_electionTimeout() / 2;

//	std::string config_filename0 = "raft_0.json";
//	SJTU::Server server0(config_filename0);
//
//	server0.Init();
//	server0.StartUp();
//	const auto timeout = server0.GetInfo().get_electionTimeout() / 2;
//	const ServerId &id = server0.GetInfo().get_local();
//	myServer server(id.toString());
//	std::cout << "timeout " << timeout << std::endl;
//
//	std::vector<std::unique_ptr<RaftPeerClientImpl> > vClient;
//	for (int i = 0, appendTime = 10; i < appendTime; ++i) {
//		vClient.push_back(std::make_unique<RaftPeerClientImpl>(id));
//
//		vClient.back()->th = boost::thread([&vClient]() mutable {
//			grpc::ClientContext ctx;
//			PbAppendEntriesRequest msg;
//			PbAppendEntriesResponse rsp;
//			msg.set_term(0);
//
//			ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(30));
//			grpc::Status status = vClient.back()->stub_->AppendEntriesRPC(&ctx, msg, &rsp);
//			printf("rpc sent\n");
//			printf("%s\n", status.error_details().c_str());
//			printf("%s\n", status.error_message().c_str());
//			printf("%d\n", status.error_code());
//			printf("%lld\n", rsp.term());
//		});
//		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
//	}
//	sleep(10);
	return 0;
}