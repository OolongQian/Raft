// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: raft_peer.proto

#include "../../../include/raft/raft_proto/raft_peer.grpc.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>

static const char *RaftPeerService_method_names[] = {
		"/RaftPeerService/AppendEntriesRPC",
		"/RaftPeerService/RequestVoteRPC",
};

std::unique_ptr<RaftPeerService::Stub>
RaftPeerService::NewStub(const std::shared_ptr<::grpc::ChannelInterface> &channel, const ::grpc::StubOptions &options) {
	(void) options;
	std::unique_ptr<RaftPeerService::Stub> stub(new RaftPeerService::Stub(channel));
	return stub;
}

RaftPeerService::Stub::Stub(const std::shared_ptr<::grpc::ChannelInterface> &channel)
		: channel_(channel),
			rpcmethod_AppendEntriesRPC_(RaftPeerService_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel),
			rpcmethod_RequestVoteRPC_(RaftPeerService_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel) {}

::grpc::Status
RaftPeerService::Stub::AppendEntriesRPC(::grpc::ClientContext *context, const ::PbAppendEntriesRequest &request,
																				::PbAppendEntriesResponse *response) {
	return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_AppendEntriesRPC_, context, request, response);
}

::grpc::ClientAsyncResponseReader<::PbAppendEntriesResponse> *
RaftPeerService::Stub::AsyncAppendEntriesRPCRaw(::grpc::ClientContext *context, const ::PbAppendEntriesRequest &request,
																								::grpc::CompletionQueue *cq) {
	return ::grpc::internal::ClientAsyncResponseReaderFactory<::PbAppendEntriesResponse>::Create(channel_.get(), cq,
																																															 rpcmethod_AppendEntriesRPC_,
																																															 context, request, true);
}

::grpc::ClientAsyncResponseReader<::PbAppendEntriesResponse> *
RaftPeerService::Stub::PrepareAsyncAppendEntriesRPCRaw(::grpc::ClientContext *context,
																											 const ::PbAppendEntriesRequest &request,
																											 ::grpc::CompletionQueue *cq) {
	return ::grpc::internal::ClientAsyncResponseReaderFactory<::PbAppendEntriesResponse>::Create(channel_.get(), cq,
																																															 rpcmethod_AppendEntriesRPC_,
																																															 context, request, false);
}

::grpc::Status
RaftPeerService::Stub::RequestVoteRPC(::grpc::ClientContext *context, const ::PbRequestVoteRequest &request,
																			::PbRequestVoteResponse *response) {
	return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_RequestVoteRPC_, context, request, response);
}

::grpc::ClientAsyncResponseReader<::PbRequestVoteResponse> *
RaftPeerService::Stub::AsyncRequestVoteRPCRaw(::grpc::ClientContext *context, const ::PbRequestVoteRequest &request,
																							::grpc::CompletionQueue *cq) {
	return ::grpc::internal::ClientAsyncResponseReaderFactory<::PbRequestVoteResponse>::Create(channel_.get(), cq,
																																														 rpcmethod_RequestVoteRPC_,
																																														 context, request, true);
}

::grpc::ClientAsyncResponseReader<::PbRequestVoteResponse> *
RaftPeerService::Stub::PrepareAsyncRequestVoteRPCRaw(::grpc::ClientContext *context,
																										 const ::PbRequestVoteRequest &request,
																										 ::grpc::CompletionQueue *cq) {
	return ::grpc::internal::ClientAsyncResponseReaderFactory<::PbRequestVoteResponse>::Create(channel_.get(), cq,
																																														 rpcmethod_RequestVoteRPC_,
																																														 context, request, false);
}

RaftPeerService::Service::Service() {
	AddMethod(new ::grpc::internal::RpcServiceMethod(
			RaftPeerService_method_names[0],
			::grpc::internal::RpcMethod::NORMAL_RPC,
			new ::grpc::internal::RpcMethodHandler<RaftPeerService::Service, ::PbAppendEntriesRequest, ::PbAppendEntriesResponse>(
					std::mem_fn(&RaftPeerService::Service::AppendEntriesRPC), this)));
	AddMethod(new ::grpc::internal::RpcServiceMethod(
			RaftPeerService_method_names[1],
			::grpc::internal::RpcMethod::NORMAL_RPC,
			new ::grpc::internal::RpcMethodHandler<RaftPeerService::Service, ::PbRequestVoteRequest, ::PbRequestVoteResponse>(
					std::mem_fn(&RaftPeerService::Service::RequestVoteRPC), this)));
}

RaftPeerService::Service::~Service() {
}

::grpc::Status
RaftPeerService::Service::AppendEntriesRPC(::grpc::ServerContext *context, const ::PbAppendEntriesRequest *request,
																					 ::PbAppendEntriesResponse *response) {
	(void) context;
	(void) request;
	(void) response;
	return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status
RaftPeerService::Service::RequestVoteRPC(::grpc::ServerContext *context, const ::PbRequestVoteRequest *request,
																				 ::PbRequestVoteResponse *response) {
	(void) context;
	(void) request;
	(void) response;
	return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


