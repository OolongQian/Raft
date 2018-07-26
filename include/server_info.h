#pragma once

#include "common.h"

#include <cstdint>
#include <vector>
#include <string>

namespace SJTU {

	class ServerInfo {
	public:
		void load(const std::string &filename);

		void save(const std::string &filename);

	private:
		ServerId local;
		std::vector<ServerId> srvList;
		std::uint64_t electionTimeout;
	};
};
