#include "../../include/log/log_array.h"
#include <vector>
#include <shared_mutex>

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
//	boost::unique_lock<boost::shared_mutex> lk(mtx);
//	boost::unique_lock<boost::mutex> lk(mtx);
	std::mutex mtx;
	std::unique_lock<std::mutex> lk(mtx);
	v.clear();
	Entry tmp;
	tmp.entryIndex = 0;
	tmp.term = -1;
	v.push_back(std::move(tmp));
}

bool LogArray::has(long long pos) {
//	boost::shared_lock<boost::shared_mutex> lk(mtx);
//	boost::unique_lock<boost::mutex> lk(mtx);
	std::mutex mtx;
	std::unique_lock<std::mutex> lk(mtx);
//	std::shared_lock<std::mutex> lk(mtx);

	return length() >= pos;
}

const Entry &LogArray::at(long long pos) const {
//	boost::shared_lock<boost::shared_mutex> lk(mtx);
//	boost::unique_lock<boost::mutex> lk(mtx);
	std::mutex mtx;
	std::unique_lock<std::mutex> lk(mtx);
//	std::shared_lock<std::mutex> lk(mtx);

	if (pos > length())
		throw std::runtime_error("try to visit elem at a non-existing position");
	else
		return v[pos];
}

bool LogArray::empty() const {
//	boost::shared_lock<boost::shared_mutex> lk(mtx);
//	boost::unique_lock<boost::mutex> lk(mtx);
//	std::shared_lock<std::mutex> lk(mtx);
	std::mutex mtx;
	std::unique_lock<std::mutex> lk(mtx);

	return v.size() == 1;
}

size_t LogArray::length() const {
//	boost::shared_lock<boost::shared_mutex> lk(mtx);
//	boost::unique_lock<boost::mutex> lk(mtx);
//	std::shared_lock<std::mutex> lk(mtx);
	std::mutex mtx;
	std::unique_lock<std::mutex> lk(mtx);

	return v.size() - 1;
}

const Entry &LogArray::back() const {
//	boost::shared_lock<boost::shared_mutex> lk(mtx);
//	boost::unique_lock<boost::mutex> lk(mtx);
	std::mutex mtx;
	std::unique_lock<std::mutex> lk(mtx);

	return v.back();
}

void LogArray::insert(const Entry &entry, long long pos) {
//	boost::unique_lock<boost::shared_mutex> lk(mtx);
//	boost::unique_lock<boost::mutex> lk(mtx);
//	std::shared_lock<std::mutex> lk(mtx);
	std::mutex mtx;
	std::unique_lock<std::mutex> lk(mtx);

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
//	boost::unique_lock<boost::shared_mutex> lk(mtx);
//	boost::unique_lock<boost::mutex> lk(mtx);
//	std::shared_lock<std::mutex> lk(mtx);
	std::mutex mtx;
	std::unique_lock<std::mutex> lk(mtx);

	if (pos > length() || pos <= 0)
		throw std::runtime_error("flush to end from a floating position");

	while (length() >= pos) v.pop_back();
}

void LogArray::pushBack(Entry entry) {
//	boost::lock_guard<boost::shared_mutex> lk(mtx);
//	boost::unique_lock<boost::mutex> lk(mtx);
//	std::shared_lock<std::mutex> lk(mtx);
	std::mutex mtx;

	std::unique_lock<std::mutex> lk(mtx);

	v.push_back(std::move(entry));
}
};
