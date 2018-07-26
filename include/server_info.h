#pragma once

#include "common.h"
#include "macro.h"

#include <cstdint>
#include <vector>
#include <string>

namespace SJTU {
	class ServerInfo {
	public:
		void load(const std::string &filename);

		void save(const std::string &filename);

		GEN_CONST_HANDLE(local);

		GEN_CONST_HANDLE(srvList);

		GEN_CONST_HANDLE(electionTimeout);

	private:
		ServerId local;
		std::vector<ServerId> srvList;
		std::uint64_t electionTimeout;
	};
};
