// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: raft_peer.proto
#ifndef GRPC_raft_5fpeer_2eproto__INCLUDED
#define GRPC_raft_5fpeer_2eproto__INCLUDED

#include "raft_peer.pb.h"

#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;

class Channel;

class ServerCompletionQueue;

class ServerContext;
}  // namespace grpc

class RaftPeerService final {
public:
	static constexpr char const *service_full_name() {
		return "RaftPeerService";
	}

	class StubInterface {
	public:
		virtual ~StubInterface() {}

		virtual ::grpc::Status AppendEntriesRPC(::grpc::ClientContext *context, const ::PbAppendEntriesRequest &request,
																						::PbAppendEntriesResponse *response) = 0;

		std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<::PbAppendEntriesResponse>>
		AsyncAppendEntriesRPC(::grpc::ClientContext *context, const ::PbAppendEntriesRequest &request,
													::grpc::CompletionQueue *cq) {
			return std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<::PbAppendEntriesResponse>>(
					AsyncAppendEntriesRPCRaw(context, request, cq));
		}

		std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<::PbAppendEntriesResponse>>
		PrepareAsyncAppendEntriesRPC(::grpc::ClientContext *context, const ::PbAppendEntriesRequest &request,
																 ::grpc::CompletionQueue *cq) {
			return std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<::PbAppendEntriesResponse>>(
					PrepareAsyncAppendEntriesRPCRaw(context, request, cq));
		}

		virtual ::grpc::Status RequestVoteRPC(::grpc::ClientContext *context, const ::PbRequestVoteRequest &request,
																					::PbRequestVoteResponse *response) = 0;

		std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<::PbRequestVoteResponse>>
		AsyncRequestVoteRPC(::grpc::ClientContext *context, const ::PbRequestVoteRequest &request,
												::grpc::CompletionQueue *cq) {
			return std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<::PbRequestVoteResponse>>(
					AsyncRequestVoteRPCRaw(context, request, cq));
		}

		std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<::PbRequestVoteResponse>>
		PrepareAsyncRequestVoteRPC(::grpc::ClientContext *context, const ::PbRequestVoteRequest &request,
															 ::grpc::CompletionQueue *cq) {
			return std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<::PbRequestVoteResponse>>(
					PrepareAsyncRequestVoteRPCRaw(context, request, cq));
		}

		virtual ::grpc::Status
		PutRPC(::grpc::ClientContext *context, const ::PbPutRequest &request, ::PbPutResponse *response) = 0;

		std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<::PbPutResponse>>
		AsyncPutRPC(::grpc::ClientContext *context, const ::PbPutRequest &request, ::grpc::CompletionQueue *cq) {
			return std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<::PbPutResponse>>(
					AsyncPutRPCRaw(context, request, cq));
		}

		std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<::PbPutResponse>>
		PrepareAsyncPutRPC(::grpc::ClientContext *context, const ::PbPutRequest &request, ::grpc::CompletionQueue *cq) {
			return std::unique_ptr<::grpc::ClientAsyncResponseReaderInterface<::PbPutResponse>>(
					PrepareAsyncPutRPCRaw(context, request, cq));
		}

	private:
		virtual ::grpc::ClientAsyncResponseReaderInterface<::PbAppendEntriesResponse> *
		AsyncAppendEntriesRPCRaw(::grpc::ClientContext *context, const ::PbAppendEntriesRequest &request,
														 ::grpc::CompletionQueue *cq) = 0;

		virtual ::grpc::ClientAsyncResponseReaderInterface<::PbAppendEntriesResponse> *
		PrepareAsyncAppendEntriesRPCRaw(::grpc::ClientContext *context, const ::PbAppendEntriesRequest &request,
																		::grpc::CompletionQueue *cq) = 0;

		virtual ::grpc::ClientAsyncResponseReaderInterface<::PbRequestVoteResponse> *
		AsyncRequestVoteRPCRaw(::grpc::ClientContext *context, const ::PbRequestVoteRequest &request,
													 ::grpc::CompletionQueue *cq) = 0;

		virtual ::grpc::ClientAsyncResponseReaderInterface<::PbRequestVoteResponse> *
		PrepareAsyncRequestVoteRPCRaw(::grpc::ClientContext *context, const ::PbRequestVoteRequest &request,
																	::grpc::CompletionQueue *cq) = 0;

		virtual ::grpc::ClientAsyncResponseReaderInterface<::PbPutResponse> *
		AsyncPutRPCRaw(::grpc::ClientContext *context, const ::PbPutRequest &request, ::grpc::CompletionQueue *cq) = 0;

		virtual ::grpc::ClientAsyncResponseReaderInterface<::PbPutResponse> *
		PrepareAsyncPutRPCRaw(::grpc::ClientContext *context, const ::PbPutRequest &request,
													::grpc::CompletionQueue *cq) = 0;
	};

	class Stub final : public StubInterface {
	public:
		Stub(const std::shared_ptr<::grpc::ChannelInterface> &channel);

		::grpc::Status AppendEntriesRPC(::grpc::ClientContext *context, const ::PbAppendEntriesRequest &request,
																		::PbAppendEntriesResponse *response) override;

		std::unique_ptr<::grpc::ClientAsyncResponseReader<::PbAppendEntriesResponse>>
		AsyncAppendEntriesRPC(::grpc::ClientContext *context, const ::PbAppendEntriesRequest &request,
													::grpc::CompletionQueue *cq) {
			return std::unique_ptr<::grpc::ClientAsyncResponseReader<::PbAppendEntriesResponse>>(
					AsyncAppendEntriesRPCRaw(context, request, cq));
		}

		std::unique_ptr<::grpc::ClientAsyncResponseReader<::PbAppendEntriesResponse>>
		PrepareAsyncAppendEntriesRPC(::grpc::ClientContext *context, const ::PbAppendEntriesRequest &request,
																 ::grpc::CompletionQueue *cq) {
			return std::unique_ptr<::grpc::ClientAsyncResponseReader<::PbAppendEntriesResponse>>(
					PrepareAsyncAppendEntriesRPCRaw(context, request, cq));
		}

		::grpc::Status RequestVoteRPC(::grpc::ClientContext *context, const ::PbRequestVoteRequest &request,
																	::PbRequestVoteResponse *response) override;

		std::unique_ptr<::grpc::ClientAsyncResponseReader<::PbRequestVoteResponse>>
		AsyncRequestVoteRPC(::grpc::ClientContext *context, const ::PbRequestVoteRequest &request,
												::grpc::CompletionQueue *cq) {
			return std::unique_ptr<::grpc::ClientAsyncResponseReader<::PbRequestVoteResponse>>(
					AsyncRequestVoteRPCRaw(context, request, cq));
		}

		std::unique_ptr<::grpc::ClientAsyncResponseReader<::PbRequestVoteResponse>>
		PrepareAsyncRequestVoteRPC(::grpc::ClientContext *context, const ::PbRequestVoteRequest &request,
															 ::grpc::CompletionQueue *cq) {
			return std::unique_ptr<::grpc::ClientAsyncResponseReader<::PbRequestVoteResponse>>(
					PrepareAsyncRequestVoteRPCRaw(context, request, cq));
		}

		::grpc::Status
		PutRPC(::grpc::ClientContext *context, const ::PbPutRequest &request, ::PbPutResponse *response) override;

		std::unique_ptr<::grpc::ClientAsyncResponseReader<::PbPutResponse>>
		AsyncPutRPC(::grpc::ClientContext *context, const ::PbPutRequest &request, ::grpc::CompletionQueue *cq) {
			return std::unique_ptr<::grpc::ClientAsyncResponseReader<::PbPutResponse>>(AsyncPutRPCRaw(context, request, cq));
		}

		std::unique_ptr<::grpc::ClientAsyncResponseReader<::PbPutResponse>>
		PrepareAsyncPutRPC(::grpc::ClientContext *context, const ::PbPutRequest &request, ::grpc::CompletionQueue *cq) {
			return std::unique_ptr<::grpc::ClientAsyncResponseReader<::PbPutResponse>>(
					PrepareAsyncPutRPCRaw(context, request, cq));
		}

	private:
		std::shared_ptr<::grpc::ChannelInterface> channel_;

		::grpc::ClientAsyncResponseReader<::PbAppendEntriesResponse> *
		AsyncAppendEntriesRPCRaw(::grpc::ClientContext *context, const ::PbAppendEntriesRequest &request,
														 ::grpc::CompletionQueue *cq) override;

		::grpc::ClientAsyncResponseReader<::PbAppendEntriesResponse> *
		PrepareAsyncAppendEntriesRPCRaw(::grpc::ClientContext *context, const ::PbAppendEntriesRequest &request,
																		::grpc::CompletionQueue *cq) override;

		::grpc::ClientAsyncResponseReader<::PbRequestVoteResponse> *
		AsyncRequestVoteRPCRaw(::grpc::ClientContext *context, const ::PbRequestVoteRequest &request,
													 ::grpc::CompletionQueue *cq) override;

		::grpc::ClientAsyncResponseReader<::PbRequestVoteResponse> *
		PrepareAsyncRequestVoteRPCRaw(::grpc::ClientContext *context, const ::PbRequestVoteRequest &request,
																	::grpc::CompletionQueue *cq) override;

		::grpc::ClientAsyncResponseReader<::PbPutResponse> *
		AsyncPutRPCRaw(::grpc::ClientContext *context, const ::PbPutRequest &request, ::grpc::CompletionQueue *cq) override;

		::grpc::ClientAsyncResponseReader<::PbPutResponse> *
		PrepareAsyncPutRPCRaw(::grpc::ClientContext *context, const ::PbPutRequest &request,
													::grpc::CompletionQueue *cq) override;

		const ::grpc::internal::RpcMethod rpcmethod_AppendEntriesRPC_;
		const ::grpc::internal::RpcMethod rpcmethod_RequestVoteRPC_;
		const ::grpc::internal::RpcMethod rpcmethod_PutRPC_;
	};

	static std::unique_ptr<Stub> NewStub(const std::shared_ptr<::grpc::ChannelInterface> &channel,
																			 const ::grpc::StubOptions &options = ::grpc::StubOptions());

	class Service : public ::grpc::Service {
	public:
		Service();

		virtual ~Service();

		virtual ::grpc::Status AppendEntriesRPC(::grpc::ServerContext *context, const ::PbAppendEntriesRequest *request,
																						::PbAppendEntriesResponse *response);

		virtual ::grpc::Status RequestVoteRPC(::grpc::ServerContext *context, const ::PbRequestVoteRequest *request,
																					::PbRequestVoteResponse *response);

		virtual ::grpc::Status
		PutRPC(::grpc::ServerContext *context, const ::PbPutRequest *request, ::PbPutResponse *response);
	};

	template<class BaseClass>
	class WithAsyncMethod_AppendEntriesRPC : public BaseClass {
	private:
		void BaseClassMustBeDerivedFromService(const Service *service) {}

	public:
		WithAsyncMethod_AppendEntriesRPC() {
			::grpc::Service::MarkMethodAsync(0);
		}

		~WithAsyncMethod_AppendEntriesRPC() override {
			BaseClassMustBeDerivedFromService(this);
		}

		// disable synchronous version of this method
		::grpc::Status AppendEntriesRPC(::grpc::ServerContext *context, const ::PbAppendEntriesRequest *request,
																		::PbAppendEntriesResponse *response) final override {
			abort();
			return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
		}

		void RequestAppendEntriesRPC(::grpc::ServerContext *context, ::PbAppendEntriesRequest *request,
																 ::grpc::ServerAsyncResponseWriter<::PbAppendEntriesResponse> *response,
																 ::grpc::CompletionQueue *new_call_cq, ::grpc::ServerCompletionQueue *notification_cq,
																 void *tag) {
			::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
		}
	};

	template<class BaseClass>
	class WithAsyncMethod_RequestVoteRPC : public BaseClass {
	private:
		void BaseClassMustBeDerivedFromService(const Service *service) {}

	public:
		WithAsyncMethod_RequestVoteRPC() {
			::grpc::Service::MarkMethodAsync(1);
		}

		~WithAsyncMethod_RequestVoteRPC() override {
			BaseClassMustBeDerivedFromService(this);
		}

		// disable synchronous version of this method
		::grpc::Status RequestVoteRPC(::grpc::ServerContext *context, const ::PbRequestVoteRequest *request,
																	::PbRequestVoteResponse *response) final override {
			abort();
			return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
		}

		void RequestRequestVoteRPC(::grpc::ServerContext *context, ::PbRequestVoteRequest *request,
															 ::grpc::ServerAsyncResponseWriter<::PbRequestVoteResponse> *response,
															 ::grpc::CompletionQueue *new_call_cq, ::grpc::ServerCompletionQueue *notification_cq,
															 void *tag) {
			::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
		}
	};

	template<class BaseClass>
	class WithAsyncMethod_PutRPC : public BaseClass {
	private:
		void BaseClassMustBeDerivedFromService(const Service *service) {}

	public:
		WithAsyncMethod_PutRPC() {
			::grpc::Service::MarkMethodAsync(2);
		}

		~WithAsyncMethod_PutRPC() override {
			BaseClassMustBeDerivedFromService(this);
		}

		// disable synchronous version of this method
		::grpc::Status
		PutRPC(::grpc::ServerContext *context, const ::PbPutRequest *request, ::PbPutResponse *response) final override {
			abort();
			return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
		}

		void RequestPutRPC(::grpc::ServerContext *context, ::PbPutRequest *request,
											 ::grpc::ServerAsyncResponseWriter<::PbPutResponse> *response,
											 ::grpc::CompletionQueue *new_call_cq, ::grpc::ServerCompletionQueue *notification_cq,
											 void *tag) {
			::grpc::Service::RequestAsyncUnary(2, context, request, response, new_call_cq, notification_cq, tag);
		}
	};

	typedef WithAsyncMethod_AppendEntriesRPC<WithAsyncMethod_RequestVoteRPC<WithAsyncMethod_PutRPC<Service> > > AsyncService;

	template<class BaseClass>
	class WithGenericMethod_AppendEntriesRPC : public BaseClass {
	private:
		void BaseClassMustBeDerivedFromService(const Service *service) {}

	public:
		WithGenericMethod_AppendEntriesRPC() {
			::grpc::Service::MarkMethodGeneric(0);
		}

		~WithGenericMethod_AppendEntriesRPC() override {
			BaseClassMustBeDerivedFromService(this);
		}

		// disable synchronous version of this method
		::grpc::Status AppendEntriesRPC(::grpc::ServerContext *context, const ::PbAppendEntriesRequest *request,
																		::PbAppendEntriesResponse *response) final override {
			abort();
			return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
		}
	};

	template<class BaseClass>
	class WithGenericMethod_RequestVoteRPC : public BaseClass {
	private:
		void BaseClassMustBeDerivedFromService(const Service *service) {}

	public:
		WithGenericMethod_RequestVoteRPC() {
			::grpc::Service::MarkMethodGeneric(1);
		}

		~WithGenericMethod_RequestVoteRPC() override {
			BaseClassMustBeDerivedFromService(this);
		}

		// disable synchronous version of this method
		::grpc::Status RequestVoteRPC(::grpc::ServerContext *context, const ::PbRequestVoteRequest *request,
																	::PbRequestVoteResponse *response) final override {
			abort();
			return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
		}
	};

	template<class BaseClass>
	class WithGenericMethod_PutRPC : public BaseClass {
	private:
		void BaseClassMustBeDerivedFromService(const Service *service) {}

	public:
		WithGenericMethod_PutRPC() {
			::grpc::Service::MarkMethodGeneric(2);
		}

		~WithGenericMethod_PutRPC() override {
			BaseClassMustBeDerivedFromService(this);
		}

		// disable synchronous version of this method
		::grpc::Status
		PutRPC(::grpc::ServerContext *context, const ::PbPutRequest *request, ::PbPutResponse *response) final override {
			abort();
			return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
		}
	};

	template<class BaseClass>
	class WithStreamedUnaryMethod_AppendEntriesRPC : public BaseClass {
	private:
		void BaseClassMustBeDerivedFromService(const Service *service) {}

	public:
		WithStreamedUnaryMethod_AppendEntriesRPC() {
			::grpc::Service::MarkMethodStreamed(0,
																					new ::grpc::internal::StreamedUnaryHandler<::PbAppendEntriesRequest, ::PbAppendEntriesResponse>(
																							std::bind(
																									&WithStreamedUnaryMethod_AppendEntriesRPC<BaseClass>::StreamedAppendEntriesRPC,
																									this, std::placeholders::_1, std::placeholders::_2)));
		}

		~WithStreamedUnaryMethod_AppendEntriesRPC() override {
			BaseClassMustBeDerivedFromService(this);
		}

		// disable regular version of this method
		::grpc::Status AppendEntriesRPC(::grpc::ServerContext *context, const ::PbAppendEntriesRequest *request,
																		::PbAppendEntriesResponse *response) final override {
			abort();
			return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
		}

		// replace default version of method with streamed unary
		virtual ::grpc::Status StreamedAppendEntriesRPC(::grpc::ServerContext *context,
																										::grpc::ServerUnaryStreamer<::PbAppendEntriesRequest, ::PbAppendEntriesResponse> *server_unary_streamer) = 0;
	};

	template<class BaseClass>
	class WithStreamedUnaryMethod_RequestVoteRPC : public BaseClass {
	private:
		void BaseClassMustBeDerivedFromService(const Service *service) {}

	public:
		WithStreamedUnaryMethod_RequestVoteRPC() {
			::grpc::Service::MarkMethodStreamed(1,
																					new ::grpc::internal::StreamedUnaryHandler<::PbRequestVoteRequest, ::PbRequestVoteResponse>(
																							std::bind(
																									&WithStreamedUnaryMethod_RequestVoteRPC<BaseClass>::StreamedRequestVoteRPC,
																									this, std::placeholders::_1, std::placeholders::_2)));
		}

		~WithStreamedUnaryMethod_RequestVoteRPC() override {
			BaseClassMustBeDerivedFromService(this);
		}

		// disable regular version of this method
		::grpc::Status RequestVoteRPC(::grpc::ServerContext *context, const ::PbRequestVoteRequest *request,
																	::PbRequestVoteResponse *response) final override {
			abort();
			return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
		}

		// replace default version of method with streamed unary
		virtual ::grpc::Status StreamedRequestVoteRPC(::grpc::ServerContext *context,
																									::grpc::ServerUnaryStreamer<::PbRequestVoteRequest, ::PbRequestVoteResponse> *server_unary_streamer) = 0;
	};

	template<class BaseClass>
	class WithStreamedUnaryMethod_PutRPC : public BaseClass {
	private:
		void BaseClassMustBeDerivedFromService(const Service *service) {}

	public:
		WithStreamedUnaryMethod_PutRPC() {
			::grpc::Service::MarkMethodStreamed(2,
																					new ::grpc::internal::StreamedUnaryHandler<::PbPutRequest, ::PbPutResponse>(
																							std::bind(&WithStreamedUnaryMethod_PutRPC<BaseClass>::StreamedPutRPC,
																												this, std::placeholders::_1, std::placeholders::_2)));
		}

		~WithStreamedUnaryMethod_PutRPC() override {
			BaseClassMustBeDerivedFromService(this);
		}

		// disable regular version of this method
		::grpc::Status
		PutRPC(::grpc::ServerContext *context, const ::PbPutRequest *request, ::PbPutResponse *response) final override {
			abort();
			return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
		}

		// replace default version of method with streamed unary
		virtual ::grpc::Status StreamedPutRPC(::grpc::ServerContext *context,
																					::grpc::ServerUnaryStreamer<::PbPutRequest, ::PbPutResponse> *server_unary_streamer) = 0;
	};

	typedef WithStreamedUnaryMethod_AppendEntriesRPC<WithStreamedUnaryMethod_RequestVoteRPC<WithStreamedUnaryMethod_PutRPC<Service> > > StreamedUnaryService;
	typedef Service SplitStreamedService;
	typedef WithStreamedUnaryMethod_AppendEntriesRPC<WithStreamedUnaryMethod_RequestVoteRPC<WithStreamedUnaryMethod_PutRPC<Service> > > StreamedService;
};


#endif  // GRPC_raft_5fpeer_2eproto__INCLUDED
