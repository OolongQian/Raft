#pragma once

#include "macro.h"

#include <cstdint>
#include <vector>
#include <string>

namespace SJTU {


	const int IdentityNum = 3;
	typedef int IdentityNo;
	const IdentityNo FollowerNo = 0;
	const IdentityNo CandidateNo = 1;
	const IdentityNo LeaderNo = 2;
	const IdentityNo DownNo = 3;

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

		/// for using of std::map
		bool operator<(const ServerId &rhs) const {
			if (addr != rhs.addr) return addr < rhs.addr;
			else return port < rhs.port;
		}

	private:
		std::string addr;
		Port port = 0;
	}; // class ServerId

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
