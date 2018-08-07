#include <grpcpp/client_context.h>
#include "../include/client.h"
#include "../include/raft/raft_proto/raft_peer.pb.h"
#include "../include/raft/raft_proto/raft_client.h"

namespace SJTU {

void Client::Config(std::string addr) {
	pClient = std::make_unique<RaftPeerClientImpl>(addr);
}

std::string Client::Put(std::string key, std::string val, int deadline_ms) {
	grpc::ClientContext ctx;
	PbClientRequest msg;
	PbClientResponse rsp;
	msg.set_command("Put");
	msg.set_key(key);
	msg.set_val(val);
	ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(deadline_ms));
	grpc::Status status = pClient->stub_->ClientRPC(&ctx, msg, &rsp);

	if (status.ok())
		return rsp.replymsg();
	else
		return status.error_message();
}

std::string Client::Get(std::string key, int deadline_ms) {
	grpc::ClientContext ctx;
	PbClientRequest msg;
	PbClientResponse rsp;
	msg.set_command("Get");
	msg.set_key(key);
	ctx.set_deadline(std::chrono::system_clock::now() + std::chrono::milliseconds(deadline_ms));
	grpc::Status status = pClient->stub_->ClientRPC(&ctx, msg, &rsp);

	if (status.ok())
		return rsp.replymsg();
	else
		return status.error_message();
}
};