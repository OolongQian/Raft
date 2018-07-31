#include "IdentityTestHelper.h"

namespace SJTU {

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
		debugContext.before_tranform = [](IdentityNo from, IdentityNo to) {
			if (from == FollowerNo && to == CandidateNo)
				throw std::runtime_error("unexpected transformation");
		};

		srvs.front()->Init();
		srvs.front()->StartUp();
		const auto timeout = srvs.front()->GetInfo().get_electionTimeout() / 2;
		auto id = srvs.front()->GetInfo().get_local();
		for (int i = 0, appendTime = 10; i < appendTime; ++i) {
			std::unique_ptr<RaftPeerClientImpl> pClient = std::make_unique<RaftPeerClientImpl>(
					grpc::CreateChannel(id.toString(), grpc::InsecureChannelCredentials()), id);
			grpc::ClientContext ctx;
			PbAppendEntriesRequest msg;
			PbAppendEntriesResponse rsp;
			msg.set_term(0);
			pClient->stub_->AppendEntriesRPC(&ctx, msg, &rsp);
			printf("rpc sent\n");
			std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
		}
		srvs.front()->ShutDown();
	}
};

int main() {
//	SJTU::Follower_Basic();
	SJTU::Follower_AppendEntry();
	return 0;
}