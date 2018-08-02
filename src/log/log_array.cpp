#include "../../include/log/log_array.h"
#include <vector>

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

LogArray::LogArray() {
	Entry tmp;
	tmp.entryIndex = tmp.term = 0;
	v.push_back(std::move(tmp));
}

	void LogArray::clear() {
		v.clear();
		LogArray();
	}

	bool LogArray::has(long long pos) {
		return length() >= pos;
	}

	const Entry &LogArray::at(long long pos) const {
		if (pos > length())
			throw std::runtime_error("try to visit elem at a non-existing position");
		else
			return v[pos];
	}

	bool LogArray::empty() const {
		return v.size() == 1;
	}

size_t LogArray::length() const {
	return v.size() - 1;
	}

	const Entry &LogArray::back() const {
		return v.back();
	}

void LogArray::insert(const Entry &entry, long long pos) {
	if (pos > length() + 1)
		throw std::runtime_error("try to insert in a floating position");
	else if (pos == length() + 1)
		pushBack(entry);
	else {
		fprintf(stderr, "LogArray is overwriting an existing entry\n");
		v[pos] = entry;
	}
}

void LogArray::flushToEnd(const long long &pos) {
	if (pos > length() || pos <= 0)
		throw std::runtime_error("flush to end from a floating position");

	while (length() >= pos) v.pop_back();
	}

	void LogArray::pushBack(Entry entry) {
		v.push_back(std::move(entry));
	}
};