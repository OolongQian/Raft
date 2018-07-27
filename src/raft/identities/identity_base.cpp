#include "../../../include/raft/identities/identity_base.h"

namespace SJTU {

	CppAppendEntriesResponse SJTU::IdentityBase::ProcsAppendEntriesFunc(CppAppendEntriesRequest) {
		return CppAppendEntriesResponse();
	}

	CppRequestVoteResponse SJTU::IdentityBase::ProcsRequestVoteFunc(CppRequestVoteRequest) {
		return CppRequestVoteResponse();
	}

};