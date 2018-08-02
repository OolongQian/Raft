#include "../../include/log/log_array.h"

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


	void LogArray::clear() {

	}

	bool LogArray::has(long long pos) {
		return false;
	}

	const Entry &LogArray::at(long long pos) const {
		Entry tmp;
		return tmp;
	}

	bool LogArray::empty() const {
		return false;
	}

	size_t LogArray::size() const {
		return 0;
	}

	const Entry &LogArray::back() const {
		return Entry();
	}

	void LogArray::insert(const Entry &, long long pos) {

	}

	void LogArray::flushToEnd(const long long pos) {

	}

	LogArray::LogArray() {
		Entry tmp;
		tmp.entryIndex = tmp.term = 0;
		v.push_back(std::move(tmp));
	}

	void LogArray::pushBack(Entry entry) {
		
	}
};