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
	static std::vector<std::unique_ptr<RaftPeerClientImpl> > vClient;
	static int cnt = 0;

	if (cnt == 0) {
		for (auto &srv : srvs) {
			if (srv == local) continue;
			vClient.push_back(std::make_unique<RaftPeerClientImpl>(srv));
		}
		++cnt;
	}

	for (int i = 0; i < vClient.size(); ++i) {
		vClient[i]->th.join();
		vClient[i]->th = boost::thread([i, currentTerm]() mutable {
			PbAppendEntriesRequest request;
			request.set_term(currentTerm);
			PbAppendEntriesResponse response;
			grpc::ClientContext context;
			context.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(50));
			grpc::Status status = vClient[i]->stub_->AppendEntriesRPC(&context, request, &response);
			if (!status.ok()) {
				printf("client number: %d ", i);
				std::cout << status.error_code() << ": " << status.error_message() << std::endl;
			} else {
				printf("client number %d, feedback received, %lld\n", i, response.term());
			}
		});
	}
	for (int i = 0; i < vClient.size(); ++i) {
		vClient[i]->th.join();
	}
}
};
