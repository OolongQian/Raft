#include "../../include/raft/state.h"
#include <fstream>

namespace SJTU {

void State::Load(std::string filename) {
	printf("initializing volatile state...\n");
	commitIndex = 0;
	lastApplied = 0;
	nextIndex.clear();
	matchIndex.clear();

	std::ifstream fin(filename, std::ios::in);
	if(fin.is_open()) {
		fin >> currentTerm;

		std::string votedForStr;
		fin >> votedForStr;
		ServerId tmp(votedForStr);
		votedFor = tmp;

		log.clear();
		size_t log_size;
		fin >> log_size;
		for(long long i = 1; i <= log_size; ++i) {
			Entry entry;
			fin >> entry.term;
			fin >> entry.command;
			fin >> entry.key;
			fin >> entry.val;
			fin >> entry.replyerId;
			fin >> entry.prmIndex;
			log.pushBack(std::move(entry));
		}
	}
	else {
		fprintf(stderr, "state file doesn't exist, initialize empty state\n");
		currentTerm = 0;
		votedFor.clear();
		log.clear();
	}
}

void State::Store(std::string filename) {
	std::ofstream fout(filename, std::ios::out);
	fout << currentTerm << std::endl;
	fout << votedFor.toString() << std::endl;
	size_t log_size = log.length();
	fout << log_size << std::endl;
	for(long long i = 1; i <= log_size; ++i) {
		Entry entry = log.at(i);
		fout << entry.term << ' ' << entry.command << ' ' << entry.key << ' ' << entry.val << ' ' <<
						entry.replyerId << entry.prmIndex << std::endl;
	}
	fout.close();
}
};