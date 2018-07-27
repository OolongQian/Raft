#ifndef RAFT_PROJ_IDENTITY_BASE_H
#define RAFT_PROJ_IDENTITY_BASE_H


#include <functional>
#include "../state.h"
#include "../raft_proto/cpp_msg_wrapper.h"

namespace SJTU {
	/**
	 * A base class
	 * */
	class IdentityBase {
	public:
//		IdentityBase() = default;

		explicit IdentityBase(State &state, std::function<void(int)> transformer) :
				state_(state), identity_transformer(std::move(transformer)) { ; }

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
		std::function<void(int)> identity_transformer;
	};
};

#endif //RAFT_PROJ_IDENTITY_BASE_H
