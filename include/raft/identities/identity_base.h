#ifndef RAFT_PROJ_IDENTITY_BASE_H
#define RAFT_PROJ_IDENTITY_BASE_H


#include <functional>
#include "../state.h"
#include "../raft_proto/cpp_msg_wrapper.h"
#include "../raft_proto/raft_peer_client.h"
#include "../timer/timer.h"

namespace SJTU {
	/**
	 * A base class
	 * */
	class IdentityBase {
	public:
//		IdentityBase() = default;

		explicit IdentityBase(State &state, Timer &timer, std::function<void(int)> transformer,
													std::vector<RaftPeerClientImpl> &client_ends) :
				state_(state), timer_(timer), identity_transformer(std::move(transformer)), client_ends_(client_ends) {}

		virtual ~IdentityBase() { ; }

		/// define two pure virtual functions.
		/// look up virtual functions' definitions clearly.

		virtual void init() = 0;

		virtual void leave() = 0;

		virtual CppAppendEntriesResponse ProcsAppendEntriesFunc(CppAppendEntriesRequest);

		virtual CppRequestVoteResponse ProcsRequestVoteFunc(CppRequestVoteRequest);

		virtual void TimeOutFunc() = 0;

	protected:
		State &state_;
		Timer &timer_;
		std::function<void(int)> identity_transformer;
		std::vector<RaftPeerClientImpl> &client_ends_;
	};
};

#endif //RAFT_PROJ_IDENTITY_BASE_H
