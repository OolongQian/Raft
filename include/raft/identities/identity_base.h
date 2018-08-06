#ifndef RAFT_PROJ_IDENTITY_BASE_H
#define RAFT_PROJ_IDENTITY_BASE_H


#include <functional>
#include "../state.h"
#include "../raft_proto/cpp_msg_wrapper.h"
#include "../raft_proto/raft_client.h"
#include "../timer/timer.h"
#include "../../server_info.h"
#include "../synchronous_queue/apply_queue.h"

namespace SJTU {

	class IdentityBase {
	public:
		explicit IdentityBase(State &state, Timer &timer, std::function<void(int)> transformer,
													std::vector<std::unique_ptr<RaftPeerClientImpl> > &client_ends, boost::atomic<bool> &paused,
													const ServerInfo &info, ApplyQueue &apply_queue) :
				state_(state), timer_(timer), identity_transformer(std::move(transformer)), client_ends_(client_ends),
				paused(paused), info(info), apply_queue(apply_queue) {}

		virtual ~IdentityBase() { ; }

		/// define two pure virtual functions.
		/// look up virtual functions' definitions clearly.

		virtual void init() = 0;

		virtual void leave() = 0;

		/**
		 * ProcsAppendEntriesFunc and ProcsRequestVoteFunc are two virtual functions implmented by
		 * three candidates. They are bound by raft into server_ends_' function adapters, and invoked
		 * by monitoring server_ends_.
		 *
		 * When raft receives other servers' requests, they generate responses based on their current
		 * status meanwhile, in term, modify themselves.
		 *
		 * I have implemented response generation without self-modification.
		 * I'm going to work on self-modification.
		 * */
		virtual void ProcsAppendEntriesFunc(const PbAppendEntriesRequest *, PbAppendEntriesResponse *);

		/**
		 * (In current naive implementation, because of no client, all clients will vote
		 * for the requester kindly.)
		 * Above is history now.
		 *
		 * */
		virtual void ProcsRequestVoteFunc(const PbRequestVoteRequest *, PbRequestVoteResponse *);

		virtual void ProcsPutFunc(const PbPutRequest *, PbPutResponse *);

		/**
		 * Timeout functions don't need to be bound to timer,
		 * define a timeoutFuncAdapter in raft or just use a lambda expression.
		 * */
		virtual void TimeOutFunc() = 0;


	protected:
		State &state_;

		/**
	   * Timer is bound into identities not for functionality (has been provided by raft apdapter),
	 	 * but for pause and reset.
	 	 *
	 	 * The stop and restart are completed in init and leave functions.
	 	 * */
		Timer &timer_;

		/**
		 * This identity_transformer is bound to raft's "identity_transform" function, which
		 * pushes a identity_transform lambda function into eventQueue and executed by another
		 * thread. It's the same as invoking by timer_.
		 * */
		std::function<void(int)> identity_transformer;
		std::vector<std::unique_ptr<RaftPeerClientImpl> > &client_ends_;
		boost::atomic<bool> &paused;
		const ServerInfo &info;

		/// if there has been one transformation undergoing, the same transformation shouldn't be applied repeatedly.
		boost::atomic<bool> transforming{false};

		ApplyQueue &apply_queue;


	protected:
		/**
		 * When client applies Put to a non-leader server, it needs to broadcast this request so that leader can hear.
		 * But meanwhile, other servers have to ignore it. 
		 * */
		virtual void ProcsClientPutFunc(const PbPutRequest *request, PbPutResponse *response);

		virtual void ProcsPeerPutFunc(const PbPutRequest *request, PbPutResponse *response);
	};
};

#endif //RAFT_PROJ_IDENTITY_BASE_H
