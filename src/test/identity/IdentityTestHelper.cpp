#include "IdentityTestHelper.h"

namespace SJTU {

	std::vector<std::unique_ptr<Server>> IdentityTestHelper::makeServers(size_t num) {
		assert(num <= 5);
		std::vector<std::unique_ptr<Server>> res;
		for (int i = 0; i < (int) num; ++i) {
			std::string filename = "raft_" + std::to_string(i) + ".json";
			auto tmp = std::make_unique<Server>(filename);
			res.emplace_back(std::move(tmp));
		}
		return res;
	}

	void
	IdentityTestHelper::sendHeartBeat(const std::vector<ServerId> &srvs, const ServerId &local, long long currentTerm) {
		for (auto &srv : srvs) {
			if (srv == local)
				continue;

			std::unique_ptr<RaftPeerClientImpl> pClient = std::make_unique<RaftPeerClientImpl>(srv);

			grpc::ClientContext ctx;
			PbAppendEntriesRequest msg;
			PbAppendEntriesResponse rsp;
			msg.set_term(currentTerm);
			pClient->stub_->AppendEntriesRPC(&ctx, msg, &rsp);
		}
	}
};
