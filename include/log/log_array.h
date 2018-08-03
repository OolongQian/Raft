#ifndef RAFT_PROJ_LOG_ARRAY_H
#define RAFT_PROJ_LOG_ARRAY_H

#include <string>
#include "../raft/raft_proto/raft_peer.pb.h"
#include <boost/thread/mutex.hpp>

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


	/// a adapted data structure for Entry.
	/// subIndex is one-based.
	class LogArray {
	public:
		LogArray();

		void clear();

		/// return whether there exists an elem at pos.
		bool has(long long pos);

		/// return the reference of the elem inside array.
		const Entry &at(long long pos) const;

		bool empty() const;

		size_t length() const;

		const Entry &back() const;

		void insert(const Entry &, long long pos);

		/// delete the existing entry and all that follow it, including the one at pos.
		void flushToEnd(const long long &pos);

		void pushBack(Entry);

	private:
		std::vector<Entry> v;
		std::mutex mtx;
	};
};
#endif //RAFT_PROJ_LOG_ARRAY_H
