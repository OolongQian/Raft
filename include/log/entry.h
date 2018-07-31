#ifndef RAFT_PROJ_ENTRY_H
#define RAFT_PROJ_ENTRY_H

/**
 * A container of one entry of log information.
 * */
#include <string>
#include "../raft/raft_proto/raft_peer.pb.h"

namespace SJTU {

	struct Entry {
		std::string command;
		std::string key;
		std::string val;
		long long term;
		long long entryIndex;

		Entry() = default;
//		{
//			command.clear();
//			key.clear();
//			val.clear();
//		}

		Entry(std::string command, std::string key, std::string val, long long term, long long entryIndex);

		explicit Entry(const PbAppendEntriesRequest::Entry &entry);

		PbAppendEntriesRequest_Entry Convert() const;
	};


};

#endif //RAFT_PROJ_ENTRY_H
