#include "../../include/raft/state.h"
#include <fstream>

namespace SJTU {

void State::Load(std::string filename) {
	std::ifstream fin(filename, std::ios::in);
	if(fin.is_open()) {
		fin >> currentTerm;

		std::string votedForStr;
		fin >> votedForStr;
		if (votedForStr == "empty") {
			votedFor.clear();
		} else {
			ServerId tmp(votedForStr);
			votedFor = tmp;
		}

		log.clear();
		size_t log_size;
		fin >> log_size;
		for(long long i = 1; i <= log_size; ++i) {
			Entry entry;
			fin >> entry.term;
			fin >> entry.entryIndex;
			fin >> entry.command;
			fin >> entry.key;
			fin >> entry.val;
			fin >> entry.replyerId;
			fin >> entry.prmIndex;
			log.pushBack(std::move(entry));
		}

		fin >> commitIndex;
		fin >> lastApplied;
		fin.close();

	}
	else {
		fprintf(stderr, "state file doesn't exist, initialize empty state\n");
		currentTerm = 0;
		votedFor.clear();
		log.clear();
		commitIndex = 0;
		lastApplied = 0;
	}
}

void State::Store(std::string filename) {
	std::ofstream fout(filename, std::ios::out);
	fout << currentTerm << std::endl;
	if (votedFor.empty()) fout << "empty" << std::endl;
	else fout << votedFor.toString() << std::endl;
	size_t log_size = log.length();
	fout << log_size << std::endl;
	for(long long i = 1; i <= log_size; ++i) {
		Entry entry = log.at(i);
		fout << entry.term << ' ' << entry.entryIndex << ' ' << entry.command << ' ' << entry.key << ' ' << entry.val << ' '
				 <<
				 entry.replyerId << ' ' << entry.prmIndex << std::endl;
	}
	fout << commitIndex << std::endl;
	fout << lastApplied << std::endl;
	fout.close();
}
};