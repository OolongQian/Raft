#include "../../include/log/entry.h"

namespace SJTU {

	Entry::Entry(const PbAppendEntriesRequest::Entry &entry) :
			command(entry.command()), key(entry.key()), val(entry.val()), term(entry.term()),
			entryIndex(entry.entryindex()) {}

	Entry::Entry(std::string command, std::string key, std::string val, long long term, long long entryIndex) :
			command(std::move(command)), key(std::move(key)), val(std::move(val)), term(term), entryIndex(entryIndex) {}

	PbAppendEntriesRequest_Entry Entry::Convert() const {
		PbAppendEntriesRequest_Entry entry;
		entry.set_command(command);
		entry.set_key(key);
		entry.set_val(val);
		entry.set_term(term);
		entry.set_entryindex(entryIndex);
		return entry;
	}
};