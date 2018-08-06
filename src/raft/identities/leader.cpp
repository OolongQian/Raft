#include "../../../include/raft/identities/leader.h"
#include "../../../include/raft/raft_proto/raft_peer.pb.h"

#define _NOT_TRIVIAL_REQUEST

namespace SJTU {

Leader::~Leader() {

}

void Leader::init() {

	/**
	 * other threads are dead, no need to add mutex.
	 * */
	++state_.currentTerm;
	state_.votedFor.clear();
	for (const ServerId &id : info.get_srvList()) {
		state_.nextIndex[id] = state_.log.back().entryIndex + 1;    /// init to be leader's last log index + 1.
		state_.matchIndex[id] = 0;                        /// init to be 0, increase monotonically.
	}
	timer_.SetTimeOut(info.get_electionTimeout() / 2, info.get_electionTimeout() / 2);
	timer_.Start();
	transforming = false;
}

void Leader::leave() {
	transforming = true;

	timer_.Stop();
	for (size_t i = 0; i < client_ends_.size(); ++i) {
		if (client_ends_[i]->th.joinable()) {
			client_ends_[i]->th.interrupt();
			client_ends_[i]->th.join();
		}
	}
	/**
	 * Other threads are dead, no need to add mutex.
	 * */
	state_.votedFor.clear();
}

void Leader::TimeOutFunc() {
	SendHeartBeat();
}

void Leader::SendHeartBeat() {
	fprintf(stderr, "server %s is issuing sending heartbeat\n", info.get_local().toString().c_str());

	/**
	 * Join by bruteforce.
	 * */
	for (size_t i = 0; i < client_ends_.size(); ++i) {
		if (client_ends_[i]->th.joinable())
			client_ends_[i]->th.join();
	}
	for (size_t i = 0; i < client_ends_.size(); ++i) {
		client_ends_[i]->th = boost::thread([this, i]() mutable {
			PbAppendEntriesRequest request;

			size_t last_entryindex_cache = MakeHeartBeat(client_ends_[i]->id, &request);

			PbAppendEntriesResponse response;
			grpc::ClientContext context;

			context.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(50));
			client_ends_[i]->stub_->AppendEntriesRPC(&context, request, &response);

			if (response.success()) {

				state_.matchIndex[client_ends_[i]->id] = (long long) last_entryindex_cache;
				state_.nextIndex[client_ends_[i]->id] = (long long) last_entryindex_cache + 1;

				CheckCommitIndexUpdate();
			} else if (response.inconsist()) {

				--state_.nextIndex[client_ends_[i]->id];
			}

			boost::unique_lock<boost::shared_mutex> lk1(state_.curTermMtx, boost::defer_lock);
			boost::unique_lock<boost::shared_mutex> lk2(state_.votedForMtx, boost::defer_lock);
			boost::lock(lk1, lk2);

			if (state_.currentTerm < response.term()) {
				state_.currentTerm = response.term();
				state_.votedFor.clear();

				lk1.unlock();
				lk2.unlock();

				identity_transformer(FollowerNo);
			}
		});
	}
}

size_t Leader::MakeHeartBeat(const ServerId &id, PbAppendEntriesRequest *request) {
	boost::shared_lock<boost::shared_mutex> lk1(state_.curTermMtx, boost::defer_lock);
	boost::shared_lock<boost::shared_mutex> lk2(state_.nxtIdxMtx, boost::defer_lock);
	boost::shared_lock<boost::shared_mutex> lk3(state_.logMasterMtx, boost::defer_lock);
	boost::shared_lock<boost::shared_mutex> lk4(state_.cmtIdxMtx, boost::defer_lock);
	boost::lock(lk1, lk2, lk3, lk4);

	request->set_term(state_.currentTerm);
	request->set_leaderid(info.get_local().toString());
	long long nxtIdx = state_.nextIndex.at(id);
	request->set_prevlogindex(
			state_.log.at(nxtIdx - 1).entryIndex);  // previous log index is which immediately proceed the new ones.
	request->set_prevlogterm(state_.log.at(nxtIdx - 1).term);
	size_t last_index = state_.log.length();
	for (long long i = nxtIdx; i <= last_index; ++i) {
		PbAppendEntriesRequest_Entry *entry = request->add_entries();
		const Entry log_entry = state_.log.at(i);
		entry->set_term(log_entry.term);
		entry->set_key(log_entry.key);
		entry->set_val(log_entry.val);
		entry->set_command(log_entry.command);
		entry->set_entryindex(i);
		entry->set_replyerid(log_entry.replyerId);
		entry->set_prmindex(log_entry.prmIndex);
	}
	request->set_leadercommit(state_.commitIndex);
	return last_index;
}


/**
 * See the last entry of description for leaders in paper.
 * */

void Leader::CheckCommitIndexUpdate() {
	boost::unique_lock<boost::shared_mutex> lk1(state_.cmtIdxMtx, boost::defer_lock);
	boost::shared_lock<boost::shared_mutex> lk2(state_.logMasterMtx, boost::defer_lock);
	boost::shared_lock<boost::shared_mutex> lk3(state_.curTermMtx, boost::defer_lock);
	boost::shared_lock<boost::shared_mutex> lk4(state_.mtchIdxMtx, boost::defer_lock);
	boost::lock(lk1, lk2, lk3, lk4);

	long long checked_N = -1;
	long long cur_N = state_.commitIndex + 1;
	int cnt = 1;

	while (cur_N <= state_.log.back().entryIndex) {
		if (state_.log.at(cur_N).term < state_.currentTerm) {
			++cur_N;
			continue;
		} else if (state_.log.at(cur_N).term > state_.currentTerm) {
			break;
		}

		for (const ServerId &id : info.get_srvList()) {
			if (id == info.get_local()) continue;
			if (state_.matchIndex.at(id) >= cur_N)
				++cnt;
		}
		if (cnt > (info.get_srvList().size()) / 2) checked_N = cur_N;
		++cur_N;
	}
	if (checked_N == -1) {
	} else {
		state_.commitIndex = checked_N;
		apply_queue.notify();
	}
}


void Leader::ProcsPutFunc(const PbPutRequest *request, PbPutResponse *response) {
	if (request->senderid().empty()) {
		ProcsClientPutFunc(request, response);
	} else {
		ProcsPeerPutFunc(request, response);
	}
}

void Leader::ProcsClientPutFunc(const PbPutRequest *request, PbPutResponse *response) {
	fprintf(stderr, "server %s is processing client put function\n", info.get_local().toString().c_str());
	boost::shared_lock<boost::shared_mutex> lk1(state_.curTermMtx, boost::defer_lock);
	boost::unique_lock<boost::shared_mutex> lk2(state_.prmRepoIdxMtx, boost::defer_lock);
	boost::lock(lk1, lk2);

	Entry log;
	log.term = state_.currentTerm;
	log.command = "Put";
	log.key = request->key();
	log.val = request->val();
	log.entryIndex = state_.log.back().entryIndex + 1;
	log.replyerId = info.get_local().toString();
	log.prmIndex = state_.prmRepoIdx++;
	lk1.unlock();
	lk2.unlock();

	std::promise<std::string> prm;
	std::future<std::string> fut = prm.get_future();
	state_.prmRepo.insert(std::pair<long long, std::promise<std::string> >(log.prmIndex, std::move(prm)));

	boost::unique_lock<boost::shared_mutex> lk3(state_.logMasterMtx);
	state_.log.pushBack(log);
	lk3.unlock();

	response->set_replymsg(fut.get());
	response->set_success(true);
}

void Leader::ProcsPeerPutFunc(const PbPutRequest *request, PbPutResponse *response) {
	fprintf(stderr, "server %s is processing peer put function from %s\n", info.get_local().toString().c_str(),
					request->senderid().c_str());
	Entry log;
	log.term = state_.currentTerm;
	log.command = "Put";
	log.key = request->key();
	log.val = request->val();
	log.replyerId = request->senderid();
	log.prmIndex = request->prmindex();
	boost::unique_lock<boost::shared_mutex> lk(state_.logMasterMtx);
	log.entryIndex = state_.log.back().entryIndex + 1;
	state_.log.pushBack(log);
	lk.unlock();
	response->set_success(true);
}
};
