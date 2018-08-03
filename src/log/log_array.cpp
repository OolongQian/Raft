#include "../../include/log/log_array.h"
#include <vector>
#include <shared_mutex>
#include <boost/thread/pthread/shared_mutex.hpp>

#define _SYNC

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
	tmp.entryIndex = 0;
	tmp.term = -1;    /// since term starts from 0, distinguish numb term from real ones.
	v.push_back(std::move(tmp));
}

void LogArray::clear() {
#ifdef _SYNC
	boost::unique_lock<boost::shared_mutex> lk(mtx);
#endif

	v.clear();
	Entry tmp;
	tmp.entryIndex = 0;
	tmp.term = -1;
	v.push_back(std::move(tmp));
}

bool LogArray::has(long long pos) {
#ifdef _SYNC
	boost::shared_lock<boost::shared_mutex> lk(mtx);
#endif

	return length() >= pos;
}

const Entry LogArray::at(long long pos) {
#ifdef _SYNC
	boost::shared_lock<boost::shared_mutex> lk(mtx);
#endif

	if (pos > length())
		throw std::runtime_error("try to visit elem at a non-existing position");
	else
		return v[pos];
}

bool LogArray::empty() {
#ifdef _SYNC
	boost::shared_lock<boost::shared_mutex> lk(mtx);
#endif

	return v.size() == 1;
}

size_t LogArray::length() {
#ifdef _SYNC
	boost::shared_lock<boost::shared_mutex> lk(mtx);
#endif

	return v.size() - 1;
}

const Entry LogArray::back() {
#ifdef _SYNC
	boost::shared_lock<boost::shared_mutex> lk(mtx);
#endif

	return v.back();
}

void LogArray::insert(const Entry &entry, long long pos) {
#ifdef _SYNC
	boost::unique_lock<boost::shared_mutex> lk(mtx);
#endif

	size_t length = v.size() - 1;
	if (pos > length + 1)
		throw std::runtime_error("try to insert in a floating position");
	else if (pos == length + 1) {
		v.push_back(entry);
	}
	else {
		fprintf(stderr, "LogArray is overwriting an existing entry\n");
		v[pos] = entry;
	}
}

void LogArray::flushToEnd(const long long &pos) {
#ifdef _SYNC
	boost::unique_lock<boost::shared_mutex> lk(mtx);
#endif

	size_t length = v.size() - 1;
	if (pos > length || pos <= 0)
		throw std::runtime_error("flush to end from a floating position");

	while (length >= pos) {
		v.pop_back();
		length = v.size() - 1;
	}
}

void LogArray::pushBack(Entry entry) {
#ifdef _SYNC
	boost::unique_lock<boost::shared_mutex> lk(mtx);
#endif
	v.push_back(std::move(entry));
}
};
