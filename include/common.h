//
// Created by 钱苏澄 on 2018/7/26.
//

#ifndef RAFT_PROJ_COMMON_H
#define RAFT_PROJ_COMMON_H


#include <cstdint>
#include <string>
#include "macro.h"

namespace SJTU {

	const int IdentityNum = 3;
	const int FollowerNo = 0;
	const int CandidateNo = 1;
	const int LeaderNo = 2;

	using Port  = std::uint16_t;
	using PrmIdx = std::uint64_t;

	class ServerId {
	public:
		GEN_DEFAULT_CTOR_AND_ASSIGNMENT(ServerId);
		ServerId(std::string addr, Port port);

		// e.g. 127.0.0.1:1080
		ServerId(const std::string &exAddr);

		GEN_CONST_HANDLE(addr);

		GEN_CONST_HANDLE(port);

		std::string toString(std::string sep = ":") const;

		const bool empty() const;

		void clear();

		bool operator==(const ServerId &rhs) const {
			return addr == rhs.addr && port == rhs.port;
		}

		bool operator!=(const ServerId &rhs) const {
			return !(*this == rhs);
		}

	private:
		std::string addr;
		Port port = 0;
	}; // class ServerId
};

#endif //RAFT_PROJ_COMMON_H
