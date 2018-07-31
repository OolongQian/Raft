#ifndef RAFT_PROJ_LOG_ARRAY_H
#define RAFT_PROJ_LOG_ARRAY_H

#include "entry.h"

namespace SJTU {
	/// a adapted data structure for Entry.
	class LogArray {
	public:
		LogArray();

		void clear();

		/// return whether there exists an elem at pos.
		bool has(long long pos);

		/// return the reference of the elem inside array.
		const Entry &at(long long pos) const;

		bool empty() const;

		size_t size() const;

		const Entry &back() const;

		void insert(const Entry &, long long pos);

		/// delete the existing entry and all that follow it, including the one at pos.
		void flushToEnd(const long long pos);

	private:
		std::vector<Entry> v;
	};
};
#endif //RAFT_PROJ_LOG_ARRAY_H
