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
		debugContext.before_tranform = [&follower2Candidate](IdentityNo from, IdentityNo &to) mutable {
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
		debugContext.before_tranform = [&](IdentityNo from, IdentityNo &to) mutable {
			if (from == FollowerNo && to == CandidateNo)
				F2C++;
			else if (from == CandidateNo && to == LeaderNo)
				C2L++;
		};

		srvs.front()->Init();
		srvs.front()->StartUp();
		const auto timeout = srvs.front()->GetInfo().get_electionTimeout() / 2;
		auto id = srvs.front()->GetInfo().get_local();

		sleep(1);
		std::vector<std::unique_ptr<RaftPeerClientImpl> > vClient;
		for (int i = 0, appendTime = 10; i < appendTime; ++i) {
			vClient.push_back(std::make_unique<RaftPeerClientImpl>(id));

			vClient.back()->th = boost::thread([&vClient]() mutable {
				grpc::ClientContext ctx;
				PbAppendEntriesRequest msg;
				PbAppendEntriesResponse rsp;
				msg.set_term(100);

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
		sleep(1);
		srvs.front()->ShutDown();
		assert(F2C == 0);
		printf("create one follower, and send heartbeat to it manually, it remains follower\n");
	}

	void Candidate_Basic() {
		IdentityTestHelper helper;
		const std::size_t SrvNum = 1;
		auto srvs = helper.makeServers(SrvNum);
		auto &ctx = Raft::GetDebug();
		ctx.before_tranform = [](IdentityNo from, IdentityNo &to) mutable {
			if (from == FollowerNo) throw std::runtime_error("unexpected test");
			if (from != DownNo && to != CandidateNo) throw std::runtime_error("transform not to candidate");
			to = to == DownNo ? DownNo : CandidateNo;
		};
		srvs[0]->Init();
		srvs[0]->StartUp();
		sleep(5);
		srvs[0]->ShutDown();
	}

	void CandidateNaive() {
		IdentityTestHelper helper;
		const std::size_t SrvNum = 3;
		auto srvs = helper.makeServers(SrvNum);
		const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();
		std::atomic<int> candidate2Follower{0}, candidate2Leader{0};

		for (auto &srv : srvs) {
			srv->Init();
			RaftDebugContext &ctx = srv->GetCtx();

			ctx.before_tranform = ([&](IdentityNo from, IdentityNo &to) mutable {
				if (from == CandidateNo && to == LeaderNo) {
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

	void PutBasic() {
		IdentityTestHelper helper;
		const std::size_t SrvNum = 1;
		auto srvs = helper.makeServers(SrvNum);
		const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();

		auto &srv = srvs.front();
		auto id = srvs.front()->GetInfo().get_local();
		srv->Init();
		srv->StartUp();
		std::unique_ptr<RaftPeerClientImpl> client;
		client = std::make_unique<RaftPeerClientImpl>(id);

		for (int i = 0; i < 10; ++i) {
			client->th = boost::thread([&client, i]() mutable {
				grpc::ClientContext ctx;
				PbPutRequest msg;
				PbPutResponse rsp;
				std::string str_key = "shit";
				std::string str_val = "dick";
				str_key += char('0' + i);
				str_val += char('0' + i);
				msg.set_key(str_key);
				msg.set_val(str_val);

				ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(100));
				grpc::Status status = client->stub_->PutRPC(&ctx, msg, &rsp);
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

	void PutNaive() {
		IdentityTestHelper helper;
		const std::size_t SrvNum = 1;
		auto srvs = helper.makeServers(SrvNum);
		const auto ElectionTimeout = srvs.front()->GetInfo().get_electionTimeout();

		auto &srv = srvs.front();

		srv->Init();

		RaftDebugContext &context = srv->GetCtx();
		std::atomic<int> candidate2Leader{0};

		context.before_tranform = ([&](IdentityNo from, IdentityNo &to) mutable {
			if (to == CandidateNo) {
				to = LeaderNo;
				++candidate2Leader;
			}
		});

		srv->StartUp();
		while (candidate2Leader != 1);

		auto id = srvs.front()->GetInfo().get_local();
		std::unique_ptr<RaftPeerClientImpl> client;
		client = std::make_unique<RaftPeerClientImpl>(id);

		for (int i = 0; i < 10; ++i) {
			client->th = boost::thread([&client, i]() mutable {
				grpc::ClientContext ctx;
				PbPutRequest msg;
				PbPutResponse rsp;
				std::string str_key = "shit";
				std::string str_val = "dick";
				str_key += char('0' + i);
				str_val += char('0' + i);
				msg.set_key(str_key);
				msg.set_val(str_val);

				ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(100));
				grpc::Status status = client->stub_->PutRPC(&ctx, msg, &rsp);
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
		printf("Put method success because of one single leader.\n");
	}
};

using namespace SJTU;

int main() {
	SJTU::PutNaive();
//	SJTU::PutBasic();
//	SJTU::Follower_Basic();
//	SJTU::Follower_AppendEntry();
//	SJTU::Candidate_Basic();
//	SJTU::CandidateNaive();
	return 0;
}
