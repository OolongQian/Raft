#ifndef RAFT_PROJ_RAFT_PEER_SERVER_H
#define RAFT_PROJ_RAFT_PEER_SERVER_H

#include "raft_peer.grpc.pb.h"
#include "cpp_msg_wrapper.h"
#include "raft_server.h"

#include <iostream>
#include <cstring>
#include <mutex>
#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>
#include <boost/thread/lock_guard.hpp>
#include <boost/thread.hpp>

namespace SJTU {
	/**
	 * A class that implements interface created by gRPC
	 * */
	class RaftServer {

		using RequestVoteFunc = std::function<CppRequestVoteResponse(CppRequestVoteRequest)>;
		using AppendEntriesFunc = std::function<CppAppendEntriesResponse(CppAppendEntriesRequest)>;

		class RaftPeerServiceImpl final : public RaftPeerService::Service {
		public:
			RaftPeerServiceImpl();

			grpc::Status AppendEntriesRPC(grpc::ServerContext *context, const PbAppendEntriesRequest *request,
																		PbAppendEntriesResponse *response) override;

			grpc::Status RequestVoteRPC(grpc::ServerContext *context, const PbRequestVoteRequest *request,
																	PbRequestVoteResponse *response) override;

		public:
//			RequestVoteFunc requestVoteFunc;
//			AppendEntriesFunc appendEntriesFunc;
		};

	public:
		explicit RaftServer(const ServerId &id) : serverId(id) {}

		void BindServiceFunc(RequestVoteFunc f1, AppendEntriesFunc f2);

		void PreMonitorInit();

		void Monitor();

		void Stop();

	private:
		const ServerId &serverId;
		/**
		 * RaftPeerServiceImpl is merely a implementation function adapter,
		 * while AsycRun requires a function object adapter which implements required interfaces to run.
		 * I can also encapsulate all this in inside this adapter.
		 * */
		RaftPeerServiceImpl service;

		std::unique_ptr<grpc::Server> server;
		/**
		 * Note that each raft_server has owns an independent thread so that they work concurrently.
		 *
		 * */
		boost::thread th;
	};
};

#endif //RAFT_PROJ_RAFT_PEER_SERVER_H
