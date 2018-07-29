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

		Entry(std::string command, std::string key, std::string val, long long term, long long entryIndex) :
				command(std::move(command)), key(std::move(key)), val(std::move(val)), term(term), entryIndex(entryIndex) {}

		explicit Entry(const PbAppendEntriesRequest::Entry &entry) :
				command(entry.command()), key(entry.key()), val(entry.val()), term(entry.term()),
				entryIndex(entry.entryindex()) {}

		PbAppendEntriesRequest_Entry Convert() const {
			PbAppendEntriesRequest_Entry entry;
			entry.set_command(command);
			entry.set_key(key);
			entry.set_val(val);
			entry.set_term(term);
			entry.set_entryindex(entryIndex);
			return entry;
		}
	};


};

#endif //RAFT_PROJ_ENTRY_H
