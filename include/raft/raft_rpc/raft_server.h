#ifndef RAFT_PROJ_RAFT_SERVER_H
#define RAFT_PROJ_RAFT_SERVER_H

#include "../raft_proto/cpp_msg_wrapper.h"
#include "../raft_proto/raft_peer_service.h"
#include "../../common.h"
#include <functional>
#include <boost/thread.hpp>

namespace SJTU {
	class RaftServer {
		using RequestVoteFunc = std::function<CppRequestVoteResponse(CppRequestVoteRequest)>;
		using AppendEntriesFunc = std::function<CppAppendEntriesResponse(CppAppendEntriesRequest)>;

	public:
		explicit RaftServer(const ServerId &id) : serverId(id) {}

		void BindServiceFunc(RequestVoteFunc f1, AppendEntriesFunc f2);

		/**
		 * Setup server and monitor peer request.
		 * */
		void Monitor();

	private:
		const ServerId &serverId;

		/**
		 * RaftPeerServiceImpl is merely a implementation function adapter,
		 * while AsycRun requires a function object adapter which implements required interfaces to run.
		 * I can also encapsulate all this in inside this adapter.
		 * */
		RaftPeerServiceImpl server_end_;

		/**
		 * Note that each raft_server has owns an independent thread so that they work concurrently.
		 *
		 * */
		boost::thread th;
	};
};

#endif //RAFT_PROJ_RAFT_SERVER_H
