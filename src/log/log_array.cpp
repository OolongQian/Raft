#include "../../include/log/log_array.h"

namespace SJTU {

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
};