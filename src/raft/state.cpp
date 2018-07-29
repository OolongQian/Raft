#include "../../include/raft/state.h"

namespace SJTU {

	void State::Init() {
		printf("initializing volatile state...\n");
		commitIndex = 0;
		lastApplied = 0;
		nextIndex.clear();
		matchIndex.clear();
		Load();
	}

	void State::Load() {
		std::cerr << "persistent state is temporarily trivially initialized" << std::endl;
		currentTerm = 0;
		votedFor.clear();
		log.clear();
	}
};