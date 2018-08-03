#ifndef RAFT_PROJ_IDENTITYTESTHELPER_H
#define RAFT_PROJ_IDENTITYTESTHELPER_H

#include "../../../include/server_info.h"
#include "../../../include/server.h"


namespace SJTU {
class IdentityTestHelper {
public:
	using No = IdentityNo;

	std::vector<std::unique_ptr<Server>> makeServers(std::size_t num = 3);

	void sendHeartBeat(const std::vector<ServerId> &srvs, const ServerId &local,
										 long long currentTerm);
};
};

#endif //RAFT_PROJ_IDENTITYTESTHELPER_H
