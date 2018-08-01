#include "../include/server_info.h"

#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace SJTU {


	ServerId::ServerId(std::string addr, Port port)
			: addr(std::move(addr)), port(port) {}

	ServerId::ServerId(const std::string &exAddr) {
		auto sepPos = exAddr.find(':');
		addr = std::string(exAddr.begin(), exAddr.begin() + sepPos);
		port = std::stoi(std::string(exAddr.cbegin() + sepPos + 1, exAddr.end()));
	}

	std::string ServerId::toString(std::string sep) const {
		return addr + sep + std::to_string(port);
	}

	void ServerId::clear() {
		addr.clear();
		port = 0;
	}

	const bool ServerId::empty() const {
		return addr.empty() && port == 0;
	}

	void ServerInfo::load(const std::string &filename) {
		namespace pt = boost::property_tree;

		pt::ptree tree;
		pt::read_json(filename, tree);

		local = ServerId(tree.get<std::string>("localAddress"));
		electionTimeout = tree.get<std::uint64_t>("electionTimeout");
		for (auto &&srv : tree.get_child("serverList"))
			srvList.emplace_back(srv.second.get_value<std::string>());
	}

	void ServerInfo::save(const std::string &filename) {
		namespace pt = boost::property_tree;
		pt::ptree tree;
		tree.put("localAddress", local.toString());
		tree.put("electionTimeout", electionTimeout);
		pt::ptree jsonSrvList;
		for (auto &&id : srvList) {
			pt::ptree srv;
			srv.put("", id.toString());
			jsonSrvList.push_back(std::make_pair("", srv));
			tree.put("serverList.serverId", id.toString());
		}
		tree.add_child("serverList", jsonSrvList);
		pt::write_json(filename, tree);
	}
}
