// source: raft_peer.proto

#include "../../../include/raft/raft_proto/raft_peer.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace protobuf_raft_5fpeer_2eproto {
	extern PROTOBUF_INTERNAL_EXPORT_protobuf_raft_5fpeer_2eproto ::google::protobuf::internal::SCCInfo<0> scc_info_PbAppendEntriesRequest_Entry;
}  // namespace protobuf_raft_5fpeer_2eproto
class PbPutRequestDefaultTypeInternal {
public:
	::google::protobuf::internal::ExplicitlyConstructed<PbPutRequest>
			_instance;
} _PbPutRequest_default_instance_;

class PbPutResponseDefaultTypeInternal {
public:
	::google::protobuf::internal::ExplicitlyConstructed<PbPutResponse>
			_instance;
} _PbPutResponse_default_instance_;
class PbAppendEntriesRequest_EntryDefaultTypeInternal {
public:
  ::google::protobuf::internal::ExplicitlyConstructed<PbAppendEntriesRequest_Entry>
      _instance;
} _PbAppendEntriesRequest_Entry_default_instance_;
class PbAppendEntriesRequestDefaultTypeInternal {
public:
  ::google::protobuf::internal::ExplicitlyConstructed<PbAppendEntriesRequest>
      _instance;
} _PbAppendEntriesRequest_default_instance_;
class PbAppendEntriesResponseDefaultTypeInternal {
public:
  ::google::protobuf::internal::ExplicitlyConstructed<PbAppendEntriesResponse>
      _instance;
} _PbAppendEntriesResponse_default_instance_;
class PbRequestVoteRequestDefaultTypeInternal {
public:
  ::google::protobuf::internal::ExplicitlyConstructed<PbRequestVoteRequest>
      _instance;
} _PbRequestVoteRequest_default_instance_;
class PbRequestVoteResponseDefaultTypeInternal {
public:
  ::google::protobuf::internal::ExplicitlyConstructed<PbRequestVoteResponse>
      _instance;
} _PbRequestVoteResponse_default_instance_;
namespace protobuf_raft_5fpeer_2eproto {
	static void InitDefaultsPbPutRequest() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void *ptr = &::_PbPutRequest_default_instance_;
			new(ptr) ::PbPutRequest();
			::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
		}
		::PbPutRequest::InitAsDefaultInstance();
	}

	::google::protobuf::internal::SCCInfo<0> scc_info_PbPutRequest =
			{{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsPbPutRequest},
			 {}};

	static void InitDefaultsPbPutResponse() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void *ptr = &::_PbPutResponse_default_instance_;
			new(ptr) ::PbPutResponse();
			::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
		}
		::PbPutResponse::InitAsDefaultInstance();
	}

	::google::protobuf::internal::SCCInfo<0> scc_info_PbPutResponse =
			{{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsPbPutResponse},
			 {}};

	static void InitDefaultsPbAppendEntriesRequest_Entry() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void *ptr = &::_PbAppendEntriesRequest_Entry_default_instance_;
			new(ptr) ::PbAppendEntriesRequest_Entry();
			::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
		}
		::PbAppendEntriesRequest_Entry::InitAsDefaultInstance();
	}

	::google::protobuf::internal::SCCInfo<0> scc_info_PbAppendEntriesRequest_Entry =
			{{ATOMIC_VAR_INIT(
						::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsPbAppendEntriesRequest_Entry},
			 {}};

	static void InitDefaultsPbAppendEntriesRequest() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void *ptr = &::_PbAppendEntriesRequest_default_instance_;
			new(ptr) ::PbAppendEntriesRequest();
			::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
		}
		::PbAppendEntriesRequest::InitAsDefaultInstance();
	}

	::google::protobuf::internal::SCCInfo<1> scc_info_PbAppendEntriesRequest =
			{{ATOMIC_VAR_INIT(
						::google::protobuf::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsPbAppendEntriesRequest},
			 {
					 &protobuf_raft_5fpeer_2eproto::scc_info_PbAppendEntriesRequest_Entry.base,}};

	static void InitDefaultsPbAppendEntriesResponse() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void *ptr = &::_PbAppendEntriesResponse_default_instance_;
			new(ptr) ::PbAppendEntriesResponse();
			::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
		}
		::PbAppendEntriesResponse::InitAsDefaultInstance();
	}

	::google::protobuf::internal::SCCInfo<0> scc_info_PbAppendEntriesResponse =
			{{ATOMIC_VAR_INIT(
						::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsPbAppendEntriesResponse},
			 {}};

	static void InitDefaultsPbRequestVoteRequest() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void *ptr = &::_PbRequestVoteRequest_default_instance_;
			new(ptr) ::PbRequestVoteRequest();
			::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
		}
		::PbRequestVoteRequest::InitAsDefaultInstance();
	}

	::google::protobuf::internal::SCCInfo<0> scc_info_PbRequestVoteRequest =
			{{ATOMIC_VAR_INIT(
						::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsPbRequestVoteRequest},
			 {}};

	static void InitDefaultsPbRequestVoteResponse() {
		GOOGLE_PROTOBUF_VERIFY_VERSION;

		{
			void *ptr = &::_PbRequestVoteResponse_default_instance_;
			new(ptr) ::PbRequestVoteResponse();
			::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
		}
		::PbRequestVoteResponse::InitAsDefaultInstance();
	}

	::google::protobuf::internal::SCCInfo<0> scc_info_PbRequestVoteResponse =
			{{ATOMIC_VAR_INIT(
						::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsPbRequestVoteResponse},
			 {}};

	void InitDefaults() {
		::google::protobuf::internal::InitSCC(&scc_info_PbPutRequest.base);
		::google::protobuf::internal::InitSCC(&scc_info_PbPutResponse.base);
		::google::protobuf::internal::InitSCC(&scc_info_PbAppendEntriesRequest_Entry.base);
		::google::protobuf::internal::InitSCC(&scc_info_PbAppendEntriesRequest.base);
		::google::protobuf::internal::InitSCC(&scc_info_PbAppendEntriesResponse.base);
		::google::protobuf::internal::InitSCC(&scc_info_PbRequestVoteRequest.base);
		::google::protobuf::internal::InitSCC(&scc_info_PbRequestVoteResponse.base);
	}

	::google::protobuf::Metadata file_level_metadata[7];

	const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
			~0u,  // no _has_bits_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbPutRequest, _internal_metadata_),
			~0u,  // no _extensions_
			~0u,  // no _oneof_case_
			~0u,  // no _weak_field_map_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbPutRequest, key_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbPutRequest, val_),
			~0u,  // no _has_bits_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbPutResponse, _internal_metadata_),
			~0u,  // no _extensions_
			~0u,  // no _oneof_case_
			~0u,  // no _weak_field_map_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbPutResponse, success_),
			~0u,  // no _has_bits_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest_Entry, _internal_metadata_),
			~0u,  // no _extensions_
			~0u,  // no _oneof_case_
			~0u,  // no _weak_field_map_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest_Entry, command_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest_Entry, key_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest_Entry, val_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest_Entry, term_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest_Entry, entryindex_),
			~0u,  // no _has_bits_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest, _internal_metadata_),
			~0u,  // no _extensions_
			~0u,  // no _oneof_case_
			~0u,  // no _weak_field_map_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest, term_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest, leaderid_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest, prevlogindex_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest, prevlogterm_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest, entries_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesRequest, leadercommit_),
			~0u,  // no _has_bits_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesResponse, _internal_metadata_),
			~0u,  // no _extensions_
			~0u,  // no _oneof_case_
			~0u,  // no _weak_field_map_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesResponse, term_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbAppendEntriesResponse, success_),
			~0u,  // no _has_bits_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbRequestVoteRequest, _internal_metadata_),
			~0u,  // no _extensions_
			~0u,  // no _oneof_case_
			~0u,  // no _weak_field_map_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbRequestVoteRequest, term_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbRequestVoteRequest, candidateid_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbRequestVoteRequest, lastlogindex_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbRequestVoteRequest, lastlogterm_),
			~0u,  // no _has_bits_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbRequestVoteResponse, _internal_metadata_),
			~0u,  // no _extensions_
			~0u,  // no _oneof_case_
			~0u,  // no _weak_field_map_
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbRequestVoteResponse, term_),
			GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::PbRequestVoteResponse, votegranted_),
	};
	static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(
			protodesc_cold) = {
			{0,  -1, sizeof(::PbPutRequest)},
			{7,  -1, sizeof(::PbPutResponse)},
			{13, -1, sizeof(::PbAppendEntriesRequest_Entry)},
			{23, -1, sizeof(::PbAppendEntriesRequest)},
			{34, -1, sizeof(::PbAppendEntriesResponse)},
			{41, -1, sizeof(::PbRequestVoteRequest)},
			{50, -1, sizeof(::PbRequestVoteResponse)},
	};

	static ::google::protobuf::Message const *const file_default_instances[] = {
			reinterpret_cast<const ::google::protobuf::Message *>(&::_PbPutRequest_default_instance_),
			reinterpret_cast<const ::google::protobuf::Message *>(&::_PbPutResponse_default_instance_),
			reinterpret_cast<const ::google::protobuf::Message *>(&::_PbAppendEntriesRequest_Entry_default_instance_),
			reinterpret_cast<const ::google::protobuf::Message *>(&::_PbAppendEntriesRequest_default_instance_),
			reinterpret_cast<const ::google::protobuf::Message *>(&::_PbAppendEntriesResponse_default_instance_),
			reinterpret_cast<const ::google::protobuf::Message *>(&::_PbRequestVoteRequest_default_instance_),
			reinterpret_cast<const ::google::protobuf::Message *>(&::_PbRequestVoteResponse_default_instance_),
	};

	void protobuf_AssignDescriptors() {
		AddDescriptors();
		AssignDescriptors(
				"raft_peer.proto", schemas, file_default_instances, TableStruct::offsets,
				file_level_metadata, NULL, NULL);
	}

	void protobuf_AssignDescriptorsOnce() {
		static ::google::protobuf::internal::once_flag once;
		::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
	}

	void protobuf_RegisterTypes(const ::std::string &) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;

	void protobuf_RegisterTypes(const ::std::string &) {
		protobuf_AssignDescriptorsOnce();
		::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 7);
	}

	void AddDescriptorsImpl() {
		InitDefaults();
		static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
				"\n\017raft_peer.proto\"(\n\014PbPutRequest\022\013\n\003key"
				"\030\001 \001(\t\022\013\n\003val\030\002 \001(\t\" \n\rPbPutResponse\022\017\n\007"
				"success\030\001 \001(\010\"\377\001\n\026PbAppendEntriesRequest"
				"\022\014\n\004term\030\001 \001(\003\022\020\n\010leaderId\030\002 \001(\t\022\024\n\014prev"
				"LogIndex\030\003 \001(\003\022\023\n\013prevLogTerm\030\004 \001(\003\022.\n\007e"
				"ntries\030\005 \003(\0132\035.PbAppendEntriesRequest.En"
				"try\022\024\n\014leaderCommit\030\006 \001(\003\032T\n\005Entry\022\017\n\007co"
				"mmand\030\001 \001(\t\022\013\n\003key\030\002 \001(\t\022\013\n\003val\030\003 \001(\t\022\014\n"
				"\004term\030\004 \001(\003\022\022\n\nentryIndex\030\005 \001(\003\"8\n\027PbApp"
				"endEntriesResponse\022\014\n\004term\030\001 \001(\003\022\017\n\007succ"
				"ess\030\002 \001(\010\"d\n\024PbRequestVoteRequest\022\014\n\004ter"
				"m\030\001 \001(\003\022\023\n\013candidateId\030\002 \001(\t\022\024\n\014lastLogI"
				"ndex\030\003 \001(\003\022\023\n\013lastLogTerm\030\004 \001(\003\":\n\025PbReq"
				"uestVoteResponse\022\014\n\004term\030\001 \001(\003\022\023\n\013voteGr"
				"anted\030\002 \001(\0102\302\001\n\017RaftPeerService\022E\n\020Appen"
				"dEntriesRPC\022\027.PbAppendEntriesRequest\032\030.P"
				"bAppendEntriesResponse\022\?\n\016RequestVoteRPC"
				"\022\025.PbRequestVoteRequest\032\026.PbRequestVoteR"
				"esponse\022\'\n\006PutRPC\022\r.PbPutRequest\032\016.PbPut"
				"Responseb\006proto3"
		};
		::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
				descriptor, 776);
		::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
				"raft_peer.proto", &protobuf_RegisterTypes);
	}

	void AddDescriptors() {
		static ::google::protobuf::internal::once_flag once;
		::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
	}
// Force AddDescriptors() to be called at dynamic initialization time.
	struct StaticDescriptorInitializer {
		StaticDescriptorInitializer() {
			AddDescriptors();
		}
	} static_descriptor_initializer;
}  // namespace protobuf_raft_5fpeer_2eproto

// ===================================================================

void PbPutRequest::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int PbPutRequest::kKeyFieldNumber;
const int PbPutRequest::kValFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

PbPutRequest::PbPutRequest()
		: ::google::protobuf::Message(), _internal_metadata_(NULL) {
	::google::protobuf::internal::InitSCC(
			&protobuf_raft_5fpeer_2eproto::scc_info_PbPutRequest.base);
	SharedCtor();
	// @@protoc_insertion_point(constructor:PbPutRequest)
}

PbPutRequest::PbPutRequest(const PbPutRequest &from)
		: ::google::protobuf::Message(),
			_internal_metadata_(NULL) {
	_internal_metadata_.MergeFrom(from._internal_metadata_);
	key_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
	if (from.key().size() > 0) {
		key_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.key_);
	}
	val_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
	if (from.val().size() > 0) {
		val_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.val_);
	}
	// @@protoc_insertion_point(copy_constructor:PbPutRequest)
}

void PbPutRequest::SharedCtor() {
	key_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
	val_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

PbPutRequest::~PbPutRequest() {
	// @@protoc_insertion_point(destructor:PbPutRequest)
	SharedDtor();
}

void PbPutRequest::SharedDtor() {
	key_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
	val_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void PbPutRequest::SetCachedSize(int size) const {
	_cached_size_.Set(size);
}

const ::google::protobuf::Descriptor *PbPutRequest::descriptor() {
	::protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
	return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const PbPutRequest &PbPutRequest::default_instance() {
	::google::protobuf::internal::InitSCC(&protobuf_raft_5fpeer_2eproto::scc_info_PbPutRequest.base);
	return *internal_default_instance();
}


void PbPutRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:PbPutRequest)
	::google::protobuf::uint32 cached_has_bits = 0;
	// Prevent compiler warnings about cached_has_bits being unused
	(void) cached_has_bits;

	key_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
	val_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
	_internal_metadata_.Clear();
}

bool PbPutRequest::MergePartialFromCodedStream(
		::google::protobuf::io::CodedInputStream *input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
	::google::protobuf::uint32 tag;
	// @@protoc_insertion_point(parse_start:PbPutRequest)
	for (;;) {
		::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
		tag = p.first;
		if (!p.second) goto handle_unusual;
		switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
			// string key = 1;
			case 1: {
				if (static_cast< ::google::protobuf::uint8>(tag) ==
						static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
					DO_(::google::protobuf::internal::WireFormatLite::ReadString(
							input, this->mutable_key()));
					DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
							this->key().data(), static_cast<int>(this->key().length()),
							::google::protobuf::internal::WireFormatLite::PARSE,
							"PbPutRequest.key"));
				} else {
					goto handle_unusual;
				}
				break;
			}

				// string val = 2;
			case 2: {
				if (static_cast< ::google::protobuf::uint8>(tag) ==
						static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
					DO_(::google::protobuf::internal::WireFormatLite::ReadString(
							input, this->mutable_val()));
					DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
							this->val().data(), static_cast<int>(this->val().length()),
							::google::protobuf::internal::WireFormatLite::PARSE,
							"PbPutRequest.val"));
				} else {
					goto handle_unusual;
				}
				break;
			}

			default: {
				handle_unusual:
				if (tag == 0) {
					goto success;
				}
				DO_(::google::protobuf::internal::WireFormat::SkipField(
						input, tag, _internal_metadata_.mutable_unknown_fields()));
				break;
			}
		}
	}
	success:
	// @@protoc_insertion_point(parse_success:PbPutRequest)
	return true;
	failure:
	// @@protoc_insertion_point(parse_failure:PbPutRequest)
	return false;
#undef DO_
}

void PbPutRequest::SerializeWithCachedSizes(
		::google::protobuf::io::CodedOutputStream *output) const {
	// @@protoc_insertion_point(serialize_start:PbPutRequest)
	::google::protobuf::uint32 cached_has_bits = 0;
	(void) cached_has_bits;

	// string key = 1;
	if (this->key().size() > 0) {
		::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->key().data(), static_cast<int>(this->key().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbPutRequest.key");
		::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
				1, this->key(), output);
	}

	// string val = 2;
	if (this->val().size() > 0) {
		::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->val().data(), static_cast<int>(this->val().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbPutRequest.val");
		::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
				2, this->val(), output);
	}

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
		::google::protobuf::internal::WireFormat::SerializeUnknownFields(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				output);
	}
	// @@protoc_insertion_point(serialize_end:PbPutRequest)
}

::google::protobuf::uint8 *PbPutRequest::InternalSerializeWithCachedSizesToArray(
		bool deterministic, ::google::protobuf::uint8 *target) const {
	(void) deterministic; // Unused
	// @@protoc_insertion_point(serialize_to_array_start:PbPutRequest)
	::google::protobuf::uint32 cached_has_bits = 0;
	(void) cached_has_bits;

	// string key = 1;
	if (this->key().size() > 0) {
		::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->key().data(), static_cast<int>(this->key().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbPutRequest.key");
		target =
				::google::protobuf::internal::WireFormatLite::WriteStringToArray(
						1, this->key(), target);
	}

	// string val = 2;
	if (this->val().size() > 0) {
		::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->val().data(), static_cast<int>(this->val().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbPutRequest.val");
		target =
				::google::protobuf::internal::WireFormatLite::WriteStringToArray(
						2, this->val(), target);
	}

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
		target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				target);
	}
	// @@protoc_insertion_point(serialize_to_array_end:PbPutRequest)
	return target;
}

size_t PbPutRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PbPutRequest)
	size_t total_size = 0;

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
		total_size +=
				::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
						(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																							: _internal_metadata_.default_instance()));
	}
	// string key = 1;
	if (this->key().size() > 0) {
		total_size += 1 +
									::google::protobuf::internal::WireFormatLite::StringSize(
											this->key());
	}

	// string val = 2;
	if (this->val().size() > 0) {
		total_size += 1 +
									::google::protobuf::internal::WireFormatLite::StringSize(
											this->val());
	}

	int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
	SetCachedSize(cached_size);
	return total_size;
}

void PbPutRequest::MergeFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_merge_from_start:PbPutRequest)
			GOOGLE_DCHECK_NE(&from, this);
	const PbPutRequest *source =
			::google::protobuf::internal::DynamicCastToGenerated<const PbPutRequest>(
					&from);
	if (source == NULL) {
		// @@protoc_insertion_point(generalized_merge_from_cast_fail:PbPutRequest)
		::google::protobuf::internal::ReflectionOps::Merge(from, this);
	} else {
		// @@protoc_insertion_point(generalized_merge_from_cast_success:PbPutRequest)
		MergeFrom(*source);
	}
}

void PbPutRequest::MergeFrom(const PbPutRequest &from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PbPutRequest)
			GOOGLE_DCHECK_NE(&from, this);
	_internal_metadata_.MergeFrom(from._internal_metadata_);
	::google::protobuf::uint32 cached_has_bits = 0;
	(void) cached_has_bits;

	if (from.key().size() > 0) {

		key_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.key_);
	}
	if (from.val().size() > 0) {

		val_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.val_);
	}
}

void PbPutRequest::CopyFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_copy_from_start:PbPutRequest)
	if (&from == this) return;
	Clear();
	MergeFrom(from);
}

void PbPutRequest::CopyFrom(const PbPutRequest &from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PbPutRequest)
	if (&from == this) return;
	Clear();
	MergeFrom(from);
}

bool PbPutRequest::IsInitialized() const {
	return true;
}

void PbPutRequest::Swap(PbPutRequest *other) {
	if (other == this) return;
	InternalSwap(other);
}

void PbPutRequest::InternalSwap(PbPutRequest *other) {
	using std::swap;
	key_.Swap(&other->key_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
						GetArenaNoVirtual());
	val_.Swap(&other->val_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
						GetArenaNoVirtual());
	_internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata PbPutRequest::GetMetadata() const {
	protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
	return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void PbPutResponse::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int PbPutResponse::kSuccessFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

PbPutResponse::PbPutResponse()
		: ::google::protobuf::Message(), _internal_metadata_(NULL) {
	::google::protobuf::internal::InitSCC(
			&protobuf_raft_5fpeer_2eproto::scc_info_PbPutResponse.base);
	SharedCtor();
	// @@protoc_insertion_point(constructor:PbPutResponse)
}

PbPutResponse::PbPutResponse(const PbPutResponse &from)
		: ::google::protobuf::Message(),
			_internal_metadata_(NULL) {
	_internal_metadata_.MergeFrom(from._internal_metadata_);
	success_ = from.success_;
	// @@protoc_insertion_point(copy_constructor:PbPutResponse)
}

void PbPutResponse::SharedCtor() {
	success_ = false;
}

PbPutResponse::~PbPutResponse() {
	// @@protoc_insertion_point(destructor:PbPutResponse)
	SharedDtor();
}

void PbPutResponse::SharedDtor() {
}

void PbPutResponse::SetCachedSize(int size) const {
	_cached_size_.Set(size);
}

const ::google::protobuf::Descriptor *PbPutResponse::descriptor() {
	::protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
	return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const PbPutResponse &PbPutResponse::default_instance() {
	::google::protobuf::internal::InitSCC(&protobuf_raft_5fpeer_2eproto::scc_info_PbPutResponse.base);
	return *internal_default_instance();
}


void PbPutResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:PbPutResponse)
	::google::protobuf::uint32 cached_has_bits = 0;
	// Prevent compiler warnings about cached_has_bits being unused
	(void) cached_has_bits;

	success_ = false;
	_internal_metadata_.Clear();
}

bool PbPutResponse::MergePartialFromCodedStream(
		::google::protobuf::io::CodedInputStream *input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
	::google::protobuf::uint32 tag;
	// @@protoc_insertion_point(parse_start:PbPutResponse)
	for (;;) {
		::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
		tag = p.first;
		if (!p.second) goto handle_unusual;
		switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
			// bool success = 1;
			case 1: {
				if (static_cast< ::google::protobuf::uint8>(tag) ==
						static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

					DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
							input, &success_)));
				} else {
					goto handle_unusual;
				}
				break;
			}

			default: {
				handle_unusual:
				if (tag == 0) {
					goto success;
				}
				DO_(::google::protobuf::internal::WireFormat::SkipField(
						input, tag, _internal_metadata_.mutable_unknown_fields()));
				break;
			}
		}
	}
	success:
	// @@protoc_insertion_point(parse_success:PbPutResponse)
	return true;
	failure:
	// @@protoc_insertion_point(parse_failure:PbPutResponse)
	return false;
#undef DO_
}

void PbPutResponse::SerializeWithCachedSizes(
		::google::protobuf::io::CodedOutputStream *output) const {
	// @@protoc_insertion_point(serialize_start:PbPutResponse)
	::google::protobuf::uint32 cached_has_bits = 0;
	(void) cached_has_bits;

	// bool success = 1;
	if (this->success() != 0) {
		::google::protobuf::internal::WireFormatLite::WriteBool(1, this->success(), output);
	}

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
		::google::protobuf::internal::WireFormat::SerializeUnknownFields(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				output);
	}
	// @@protoc_insertion_point(serialize_end:PbPutResponse)
}

::google::protobuf::uint8 *PbPutResponse::InternalSerializeWithCachedSizesToArray(
		bool deterministic, ::google::protobuf::uint8 *target) const {
	(void) deterministic; // Unused
	// @@protoc_insertion_point(serialize_to_array_start:PbPutResponse)
	::google::protobuf::uint32 cached_has_bits = 0;
	(void) cached_has_bits;

	// bool success = 1;
	if (this->success() != 0) {
		target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(1, this->success(), target);
	}

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
		target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				target);
	}
	// @@protoc_insertion_point(serialize_to_array_end:PbPutResponse)
	return target;
}

size_t PbPutResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PbPutResponse)
	size_t total_size = 0;

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
		total_size +=
				::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
						(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																							: _internal_metadata_.default_instance()));
	}
	// bool success = 1;
	if (this->success() != 0) {
		total_size += 1 + 1;
	}

	int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
	SetCachedSize(cached_size);
	return total_size;
}

void PbPutResponse::MergeFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_merge_from_start:PbPutResponse)
			GOOGLE_DCHECK_NE(&from, this);
	const PbPutResponse *source =
			::google::protobuf::internal::DynamicCastToGenerated<const PbPutResponse>(
					&from);
	if (source == NULL) {
		// @@protoc_insertion_point(generalized_merge_from_cast_fail:PbPutResponse)
		::google::protobuf::internal::ReflectionOps::Merge(from, this);
	} else {
		// @@protoc_insertion_point(generalized_merge_from_cast_success:PbPutResponse)
		MergeFrom(*source);
	}
}

void PbPutResponse::MergeFrom(const PbPutResponse &from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PbPutResponse)
			GOOGLE_DCHECK_NE(&from, this);
	_internal_metadata_.MergeFrom(from._internal_metadata_);
	::google::protobuf::uint32 cached_has_bits = 0;
	(void) cached_has_bits;

	if (from.success() != 0) {
		set_success(from.success());
	}
}

void PbPutResponse::CopyFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_copy_from_start:PbPutResponse)
	if (&from == this) return;
	Clear();
	MergeFrom(from);
}

void PbPutResponse::CopyFrom(const PbPutResponse &from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PbPutResponse)
	if (&from == this) return;
	Clear();
	MergeFrom(from);
}

bool PbPutResponse::IsInitialized() const {
	return true;
}

void PbPutResponse::Swap(PbPutResponse *other) {
	if (other == this) return;
	InternalSwap(other);
}

void PbPutResponse::InternalSwap(PbPutResponse *other) {
	using std::swap;
	swap(success_, other->success_);
	_internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata PbPutResponse::GetMetadata() const {
	protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
	return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void PbAppendEntriesRequest_Entry::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int PbAppendEntriesRequest_Entry::kCommandFieldNumber;
const int PbAppendEntriesRequest_Entry::kKeyFieldNumber;
const int PbAppendEntriesRequest_Entry::kValFieldNumber;
const int PbAppendEntriesRequest_Entry::kTermFieldNumber;
const int PbAppendEntriesRequest_Entry::kEntryIndexFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

PbAppendEntriesRequest_Entry::PbAppendEntriesRequest_Entry()
		: ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_raft_5fpeer_2eproto::scc_info_PbAppendEntriesRequest_Entry.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:PbAppendEntriesRequest.Entry)
}

PbAppendEntriesRequest_Entry::PbAppendEntriesRequest_Entry(const PbAppendEntriesRequest_Entry &from)
		: ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  command_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.command().size() > 0) {
    command_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.command_);
  }
  key_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.key().size() > 0) {
    key_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.key_);
  }
  val_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.val().size() > 0) {
    val_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.val_);
  }
	::memcpy(&term_, &from.term_,
					 static_cast<size_t>(reinterpret_cast<char *>(&entryindex_) -
															 reinterpret_cast<char *>(&term_)) + sizeof(entryindex_));
  // @@protoc_insertion_point(copy_constructor:PbAppendEntriesRequest.Entry)
}

void PbAppendEntriesRequest_Entry::SharedCtor() {
  command_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  key_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  val_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
	::memset(&term_, 0, static_cast<size_t>(
													reinterpret_cast<char *>(&entryindex_) -
													reinterpret_cast<char *>(&term_)) + sizeof(entryindex_));
}

PbAppendEntriesRequest_Entry::~PbAppendEntriesRequest_Entry() {
  // @@protoc_insertion_point(destructor:PbAppendEntriesRequest.Entry)
  SharedDtor();
}

void PbAppendEntriesRequest_Entry::SharedDtor() {
  command_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  key_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  val_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void PbAppendEntriesRequest_Entry::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

const ::google::protobuf::Descriptor *PbAppendEntriesRequest_Entry::descriptor() {
  ::protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const PbAppendEntriesRequest_Entry &PbAppendEntriesRequest_Entry::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_raft_5fpeer_2eproto::scc_info_PbAppendEntriesRequest_Entry.base);
  return *internal_default_instance();
}


void PbAppendEntriesRequest_Entry::Clear() {
// @@protoc_insertion_point(message_clear_start:PbAppendEntriesRequest.Entry)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  command_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  key_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  val_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
	::memset(&term_, 0, static_cast<size_t>(
													reinterpret_cast<char *>(&entryindex_) -
													reinterpret_cast<char *>(&term_)) + sizeof(entryindex_));
  _internal_metadata_.Clear();
}

bool PbAppendEntriesRequest_Entry::MergePartialFromCodedStream(
		::google::protobuf::io::CodedInputStream *input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:PbAppendEntriesRequest.Entry)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string command = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
							input, this->mutable_command()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
							this->command().data(), static_cast<int>(this->command().length()),
							::google::protobuf::internal::WireFormatLite::PARSE,
							"PbAppendEntriesRequest.Entry.command"));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// string key = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
							input, this->mutable_key()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
							this->key().data(), static_cast<int>(this->key().length()),
							::google::protobuf::internal::WireFormatLite::PARSE,
							"PbAppendEntriesRequest.Entry.key"));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// string val = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
							input, this->mutable_val()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
							this->val().data(), static_cast<int>(this->val().length()),
							::google::protobuf::internal::WireFormatLite::PARSE,
							"PbAppendEntriesRequest.Entry.val"));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// int64 term = 4;
			case 4: {
				if (static_cast< ::google::protobuf::uint8>(tag) ==
						static_cast< ::google::protobuf::uint8>(32u /* 32 & 0xFF */)) {

					DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
							input, &term_)));
				} else {
					goto handle_unusual;
				}
				break;
			}

				// int64 entryIndex = 5;
			case 5: {
				if (static_cast< ::google::protobuf::uint8>(tag) ==
						static_cast< ::google::protobuf::uint8>(40u /* 40 & 0xFF */)) {

					DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
							input, &entryindex_)));
				} else {
					goto handle_unusual;
				}
				break;
			}

      default: {
				handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
						input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
	success:
  // @@protoc_insertion_point(parse_success:PbAppendEntriesRequest.Entry)
  return true;
	failure:
  // @@protoc_insertion_point(parse_failure:PbAppendEntriesRequest.Entry)
  return false;
#undef DO_
}

void PbAppendEntriesRequest_Entry::SerializeWithCachedSizes(
		::google::protobuf::io::CodedOutputStream *output) const {
  // @@protoc_insertion_point(serialize_start:PbAppendEntriesRequest.Entry)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string command = 1;
  if (this->command().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->command().data(), static_cast<int>(this->command().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbAppendEntriesRequest.Entry.command");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
				1, this->command(), output);
  }

  // string key = 2;
  if (this->key().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->key().data(), static_cast<int>(this->key().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbAppendEntriesRequest.Entry.key");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
				2, this->key(), output);
  }

  // string val = 3;
  if (this->val().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->val().data(), static_cast<int>(this->val().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbAppendEntriesRequest.Entry.val");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
				3, this->val(), output);
  }

	// int64 term = 4;
	if (this->term() != 0) {
		::google::protobuf::internal::WireFormatLite::WriteInt64(4, this->term(), output);
	}

	// int64 entryIndex = 5;
	if (this->entryindex() != 0) {
		::google::protobuf::internal::WireFormatLite::WriteInt64(5, this->entryindex(), output);
	}

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				output);
  }
  // @@protoc_insertion_point(serialize_end:PbAppendEntriesRequest.Entry)
}

::google::protobuf::uint8 *PbAppendEntriesRequest_Entry::InternalSerializeWithCachedSizesToArray(
		bool deterministic, ::google::protobuf::uint8 *target) const {
	(void) deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:PbAppendEntriesRequest.Entry)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string command = 1;
  if (this->command().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->command().data(), static_cast<int>(this->command().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbAppendEntriesRequest.Entry.command");
    target =
				::google::protobuf::internal::WireFormatLite::WriteStringToArray(
						1, this->command(), target);
  }

  // string key = 2;
  if (this->key().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->key().data(), static_cast<int>(this->key().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbAppendEntriesRequest.Entry.key");
    target =
				::google::protobuf::internal::WireFormatLite::WriteStringToArray(
						2, this->key(), target);
  }

  // string val = 3;
  if (this->val().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->val().data(), static_cast<int>(this->val().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbAppendEntriesRequest.Entry.val");
    target =
				::google::protobuf::internal::WireFormatLite::WriteStringToArray(
						3, this->val(), target);
  }

	// int64 term = 4;
	if (this->term() != 0) {
		target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(4, this->term(), target);
	}

	// int64 entryIndex = 5;
	if (this->entryindex() != 0) {
		target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(5, this->entryindex(), target);
	}

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PbAppendEntriesRequest.Entry)
  return target;
}

size_t PbAppendEntriesRequest_Entry::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PbAppendEntriesRequest.Entry)
  size_t total_size = 0;

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
				::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
						(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																							: _internal_metadata_.default_instance()));
  }
  // string command = 1;
  if (this->command().size() > 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::StringSize(
											this->command());
  }

  // string key = 2;
  if (this->key().size() > 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::StringSize(
											this->key());
  }

  // string val = 3;
  if (this->val().size() > 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::StringSize(
											this->val());
  }

	// int64 term = 4;
	if (this->term() != 0) {
		total_size += 1 +
									::google::protobuf::internal::WireFormatLite::Int64Size(
											this->term());
	}

	// int64 entryIndex = 5;
	if (this->entryindex() != 0) {
		total_size += 1 +
									::google::protobuf::internal::WireFormatLite::Int64Size(
											this->entryindex());
	}

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void PbAppendEntriesRequest_Entry::MergeFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_merge_from_start:PbAppendEntriesRequest.Entry)
			GOOGLE_DCHECK_NE(&from, this);
	const PbAppendEntriesRequest_Entry *source =
      ::google::protobuf::internal::DynamicCastToGenerated<const PbAppendEntriesRequest_Entry>(
          &from);
  if (source == NULL) {
		// @@protoc_insertion_point(generalized_merge_from_cast_fail:PbAppendEntriesRequest.Entry)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
		// @@protoc_insertion_point(generalized_merge_from_cast_success:PbAppendEntriesRequest.Entry)
    MergeFrom(*source);
  }
}

void PbAppendEntriesRequest_Entry::MergeFrom(const PbAppendEntriesRequest_Entry &from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PbAppendEntriesRequest.Entry)
			GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.command().size() > 0) {

    command_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.command_);
  }
  if (from.key().size() > 0) {

    key_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.key_);
  }
  if (from.val().size() > 0) {

    val_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.val_);
  }
	if (from.term() != 0) {
		set_term(from.term());
	}
	if (from.entryindex() != 0) {
		set_entryindex(from.entryindex());
	}
}

void PbAppendEntriesRequest_Entry::CopyFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_copy_from_start:PbAppendEntriesRequest.Entry)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PbAppendEntriesRequest_Entry::CopyFrom(const PbAppendEntriesRequest_Entry &from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PbAppendEntriesRequest.Entry)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PbAppendEntriesRequest_Entry::IsInitialized() const {
  return true;
}

void PbAppendEntriesRequest_Entry::Swap(PbAppendEntriesRequest_Entry *other) {
  if (other == this) return;
  InternalSwap(other);
}

void PbAppendEntriesRequest_Entry::InternalSwap(PbAppendEntriesRequest_Entry *other) {
  using std::swap;
  command_.Swap(&other->command_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
								GetArenaNoVirtual());
  key_.Swap(&other->key_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
						GetArenaNoVirtual());
  val_.Swap(&other->val_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
						GetArenaNoVirtual());
	swap(term_, other->term_);
	swap(entryindex_, other->entryindex_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata PbAppendEntriesRequest_Entry::GetMetadata() const {
  protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void PbAppendEntriesRequest::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int PbAppendEntriesRequest::kTermFieldNumber;
const int PbAppendEntriesRequest::kLeaderIdFieldNumber;
const int PbAppendEntriesRequest::kPrevLogIndexFieldNumber;
const int PbAppendEntriesRequest::kPrevLogTermFieldNumber;
const int PbAppendEntriesRequest::kEntriesFieldNumber;
const int PbAppendEntriesRequest::kLeaderCommitFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

PbAppendEntriesRequest::PbAppendEntriesRequest()
		: ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_raft_5fpeer_2eproto::scc_info_PbAppendEntriesRequest.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:PbAppendEntriesRequest)
}

PbAppendEntriesRequest::PbAppendEntriesRequest(const PbAppendEntriesRequest &from)
		: ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      entries_(from.entries_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  leaderid_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.leaderid().size() > 0) {
    leaderid_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.leaderid_);
  }
  ::memcpy(&term_, &from.term_,
					 static_cast<size_t>(reinterpret_cast<char *>(&leadercommit_) -
															 reinterpret_cast<char *>(&term_)) + sizeof(leadercommit_));
  // @@protoc_insertion_point(copy_constructor:PbAppendEntriesRequest)
}

void PbAppendEntriesRequest::SharedCtor() {
  leaderid_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&term_, 0, static_cast<size_t>(
													reinterpret_cast<char *>(&leadercommit_) -
													reinterpret_cast<char *>(&term_)) + sizeof(leadercommit_));
}

PbAppendEntriesRequest::~PbAppendEntriesRequest() {
  // @@protoc_insertion_point(destructor:PbAppendEntriesRequest)
  SharedDtor();
}

void PbAppendEntriesRequest::SharedDtor() {
  leaderid_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void PbAppendEntriesRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

const ::google::protobuf::Descriptor *PbAppendEntriesRequest::descriptor() {
  ::protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const PbAppendEntriesRequest &PbAppendEntriesRequest::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_raft_5fpeer_2eproto::scc_info_PbAppendEntriesRequest.base);
  return *internal_default_instance();
}


void PbAppendEntriesRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:PbAppendEntriesRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  entries_.Clear();
  leaderid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&term_, 0, static_cast<size_t>(
													reinterpret_cast<char *>(&leadercommit_) -
													reinterpret_cast<char *>(&term_)) + sizeof(leadercommit_));
  _internal_metadata_.Clear();
}

bool PbAppendEntriesRequest::MergePartialFromCodedStream(
		::google::protobuf::io::CodedInputStream *input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:PbAppendEntriesRequest)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int64 term = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
							input, &term_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// string leaderId = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
							input, this->mutable_leaderid()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
							this->leaderid().data(), static_cast<int>(this->leaderid().length()),
							::google::protobuf::internal::WireFormatLite::PARSE,
							"PbAppendEntriesRequest.leaderId"));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// int64 prevLogIndex = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
							input, &prevlogindex_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// int64 prevLogTerm = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(32u /* 32 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
							input, &prevlogterm_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// repeated .PbAppendEntriesRequest.Entry entries = 5;
      case 5: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(42u /* 42 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessage(
							input, add_entries()));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// int64 leaderCommit = 6;
      case 6: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(48u /* 48 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
							input, &leadercommit_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
				handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
						input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
	success:
  // @@protoc_insertion_point(parse_success:PbAppendEntriesRequest)
  return true;
	failure:
  // @@protoc_insertion_point(parse_failure:PbAppendEntriesRequest)
  return false;
#undef DO_
}

void PbAppendEntriesRequest::SerializeWithCachedSizes(
		::google::protobuf::io::CodedOutputStream *output) const {
  // @@protoc_insertion_point(serialize_start:PbAppendEntriesRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 term = 1;
  if (this->term() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->term(), output);
  }

  // string leaderId = 2;
  if (this->leaderid().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->leaderid().data(), static_cast<int>(this->leaderid().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbAppendEntriesRequest.leaderId");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
				2, this->leaderid(), output);
  }

  // int64 prevLogIndex = 3;
  if (this->prevlogindex() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(3, this->prevlogindex(), output);
  }

  // int64 prevLogTerm = 4;
  if (this->prevlogterm() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(4, this->prevlogterm(), output);
  }

  // repeated .PbAppendEntriesRequest.Entry entries = 5;
  for (unsigned int i = 0,
					 n = static_cast<unsigned int>(this->entries_size()); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
				5,
				this->entries(static_cast<int>(i)),
				output);
  }

  // int64 leaderCommit = 6;
  if (this->leadercommit() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(6, this->leadercommit(), output);
  }

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				output);
  }
  // @@protoc_insertion_point(serialize_end:PbAppendEntriesRequest)
}

::google::protobuf::uint8 *PbAppendEntriesRequest::InternalSerializeWithCachedSizesToArray(
		bool deterministic, ::google::protobuf::uint8 *target) const {
	(void) deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:PbAppendEntriesRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 term = 1;
  if (this->term() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->term(), target);
  }

  // string leaderId = 2;
  if (this->leaderid().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->leaderid().data(), static_cast<int>(this->leaderid().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbAppendEntriesRequest.leaderId");
    target =
				::google::protobuf::internal::WireFormatLite::WriteStringToArray(
						2, this->leaderid(), target);
  }

  // int64 prevLogIndex = 3;
  if (this->prevlogindex() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(3, this->prevlogindex(), target);
  }

  // int64 prevLogTerm = 4;
  if (this->prevlogterm() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(4, this->prevlogterm(), target);
  }

  // repeated .PbAppendEntriesRequest.Entry entries = 5;
  for (unsigned int i = 0,
					 n = static_cast<unsigned int>(this->entries_size()); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
		InternalWriteMessageToArray(
        5, this->entries(static_cast<int>(i)), deterministic, target);
  }

  // int64 leaderCommit = 6;
  if (this->leadercommit() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(6, this->leadercommit(), target);
  }

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PbAppendEntriesRequest)
  return target;
}

size_t PbAppendEntriesRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PbAppendEntriesRequest)
  size_t total_size = 0;

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
				::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
						(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																							: _internal_metadata_.default_instance()));
  }
  // repeated .PbAppendEntriesRequest.Entry entries = 5;
  {
    unsigned int count = static_cast<unsigned int>(this->entries_size());
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
					::google::protobuf::internal::WireFormatLite::MessageSize(
							this->entries(static_cast<int>(i)));
    }
  }

  // string leaderId = 2;
  if (this->leaderid().size() > 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::StringSize(
											this->leaderid());
  }

  // int64 term = 1;
  if (this->term() != 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::Int64Size(
											this->term());
  }

  // int64 prevLogIndex = 3;
  if (this->prevlogindex() != 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::Int64Size(
											this->prevlogindex());
  }

  // int64 prevLogTerm = 4;
  if (this->prevlogterm() != 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::Int64Size(
											this->prevlogterm());
  }

  // int64 leaderCommit = 6;
  if (this->leadercommit() != 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::Int64Size(
											this->leadercommit());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void PbAppendEntriesRequest::MergeFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_merge_from_start:PbAppendEntriesRequest)
			GOOGLE_DCHECK_NE(&from, this);
	const PbAppendEntriesRequest *source =
      ::google::protobuf::internal::DynamicCastToGenerated<const PbAppendEntriesRequest>(
          &from);
  if (source == NULL) {
		// @@protoc_insertion_point(generalized_merge_from_cast_fail:PbAppendEntriesRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
		// @@protoc_insertion_point(generalized_merge_from_cast_success:PbAppendEntriesRequest)
    MergeFrom(*source);
  }
}

void PbAppendEntriesRequest::MergeFrom(const PbAppendEntriesRequest &from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PbAppendEntriesRequest)
			GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  entries_.MergeFrom(from.entries_);
  if (from.leaderid().size() > 0) {

    leaderid_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.leaderid_);
  }
  if (from.term() != 0) {
    set_term(from.term());
  }
  if (from.prevlogindex() != 0) {
    set_prevlogindex(from.prevlogindex());
  }
  if (from.prevlogterm() != 0) {
    set_prevlogterm(from.prevlogterm());
  }
  if (from.leadercommit() != 0) {
    set_leadercommit(from.leadercommit());
  }
}

void PbAppendEntriesRequest::CopyFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_copy_from_start:PbAppendEntriesRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PbAppendEntriesRequest::CopyFrom(const PbAppendEntriesRequest &from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PbAppendEntriesRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PbAppendEntriesRequest::IsInitialized() const {
  return true;
}

void PbAppendEntriesRequest::Swap(PbAppendEntriesRequest *other) {
  if (other == this) return;
  InternalSwap(other);
}

void PbAppendEntriesRequest::InternalSwap(PbAppendEntriesRequest *other) {
  using std::swap;
  CastToBase(&entries_)->InternalSwap(CastToBase(&other->entries_));
  leaderid_.Swap(&other->leaderid_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
								 GetArenaNoVirtual());
  swap(term_, other->term_);
  swap(prevlogindex_, other->prevlogindex_);
  swap(prevlogterm_, other->prevlogterm_);
  swap(leadercommit_, other->leadercommit_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata PbAppendEntriesRequest::GetMetadata() const {
  protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void PbAppendEntriesResponse::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int PbAppendEntriesResponse::kTermFieldNumber;
const int PbAppendEntriesResponse::kSuccessFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

PbAppendEntriesResponse::PbAppendEntriesResponse()
		: ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_raft_5fpeer_2eproto::scc_info_PbAppendEntriesResponse.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:PbAppendEntriesResponse)
}

PbAppendEntriesResponse::PbAppendEntriesResponse(const PbAppendEntriesResponse &from)
		: ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&term_, &from.term_,
					 static_cast<size_t>(reinterpret_cast<char *>(&success_) -
															 reinterpret_cast<char *>(&term_)) + sizeof(success_));
  // @@protoc_insertion_point(copy_constructor:PbAppendEntriesResponse)
}

void PbAppendEntriesResponse::SharedCtor() {
  ::memset(&term_, 0, static_cast<size_t>(
													reinterpret_cast<char *>(&success_) -
													reinterpret_cast<char *>(&term_)) + sizeof(success_));
}

PbAppendEntriesResponse::~PbAppendEntriesResponse() {
  // @@protoc_insertion_point(destructor:PbAppendEntriesResponse)
  SharedDtor();
}

void PbAppendEntriesResponse::SharedDtor() {
}

void PbAppendEntriesResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

const ::google::protobuf::Descriptor *PbAppendEntriesResponse::descriptor() {
  ::protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const PbAppendEntriesResponse &PbAppendEntriesResponse::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_raft_5fpeer_2eproto::scc_info_PbAppendEntriesResponse.base);
  return *internal_default_instance();
}


void PbAppendEntriesResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:PbAppendEntriesResponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&term_, 0, static_cast<size_t>(
													reinterpret_cast<char *>(&success_) -
													reinterpret_cast<char *>(&term_)) + sizeof(success_));
  _internal_metadata_.Clear();
}

bool PbAppendEntriesResponse::MergePartialFromCodedStream(
		::google::protobuf::io::CodedInputStream *input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:PbAppendEntriesResponse)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int64 term = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
							input, &term_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// bool success = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
							input, &success_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
				handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
						input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
	success:
  // @@protoc_insertion_point(parse_success:PbAppendEntriesResponse)
  return true;
	failure:
  // @@protoc_insertion_point(parse_failure:PbAppendEntriesResponse)
  return false;
#undef DO_
}

void PbAppendEntriesResponse::SerializeWithCachedSizes(
		::google::protobuf::io::CodedOutputStream *output) const {
  // @@protoc_insertion_point(serialize_start:PbAppendEntriesResponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 term = 1;
  if (this->term() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->term(), output);
  }

  // bool success = 2;
  if (this->success() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->success(), output);
  }

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				output);
  }
  // @@protoc_insertion_point(serialize_end:PbAppendEntriesResponse)
}

::google::protobuf::uint8 *PbAppendEntriesResponse::InternalSerializeWithCachedSizesToArray(
		bool deterministic, ::google::protobuf::uint8 *target) const {
	(void) deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:PbAppendEntriesResponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 term = 1;
  if (this->term() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->term(), target);
  }

  // bool success = 2;
  if (this->success() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->success(), target);
  }

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PbAppendEntriesResponse)
  return target;
}

size_t PbAppendEntriesResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PbAppendEntriesResponse)
  size_t total_size = 0;

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
				::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
						(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																							: _internal_metadata_.default_instance()));
  }
  // int64 term = 1;
  if (this->term() != 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::Int64Size(
											this->term());
  }

  // bool success = 2;
  if (this->success() != 0) {
    total_size += 1 + 1;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void PbAppendEntriesResponse::MergeFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_merge_from_start:PbAppendEntriesResponse)
			GOOGLE_DCHECK_NE(&from, this);
	const PbAppendEntriesResponse *source =
      ::google::protobuf::internal::DynamicCastToGenerated<const PbAppendEntriesResponse>(
          &from);
  if (source == NULL) {
		// @@protoc_insertion_point(generalized_merge_from_cast_fail:PbAppendEntriesResponse)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
		// @@protoc_insertion_point(generalized_merge_from_cast_success:PbAppendEntriesResponse)
    MergeFrom(*source);
  }
}

void PbAppendEntriesResponse::MergeFrom(const PbAppendEntriesResponse &from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PbAppendEntriesResponse)
			GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.term() != 0) {
    set_term(from.term());
  }
  if (from.success() != 0) {
    set_success(from.success());
  }
}

void PbAppendEntriesResponse::CopyFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_copy_from_start:PbAppendEntriesResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PbAppendEntriesResponse::CopyFrom(const PbAppendEntriesResponse &from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PbAppendEntriesResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PbAppendEntriesResponse::IsInitialized() const {
  return true;
}

void PbAppendEntriesResponse::Swap(PbAppendEntriesResponse *other) {
  if (other == this) return;
  InternalSwap(other);
}

void PbAppendEntriesResponse::InternalSwap(PbAppendEntriesResponse *other) {
  using std::swap;
  swap(term_, other->term_);
  swap(success_, other->success_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata PbAppendEntriesResponse::GetMetadata() const {
  protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void PbRequestVoteRequest::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int PbRequestVoteRequest::kTermFieldNumber;
const int PbRequestVoteRequest::kCandidateIdFieldNumber;
const int PbRequestVoteRequest::kLastLogIndexFieldNumber;
const int PbRequestVoteRequest::kLastLogTermFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

PbRequestVoteRequest::PbRequestVoteRequest()
		: ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_raft_5fpeer_2eproto::scc_info_PbRequestVoteRequest.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:PbRequestVoteRequest)
}

PbRequestVoteRequest::PbRequestVoteRequest(const PbRequestVoteRequest &from)
		: ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  candidateid_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.candidateid().size() > 0) {
    candidateid_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.candidateid_);
  }
  ::memcpy(&term_, &from.term_,
					 static_cast<size_t>(reinterpret_cast<char *>(&lastlogterm_) -
															 reinterpret_cast<char *>(&term_)) + sizeof(lastlogterm_));
  // @@protoc_insertion_point(copy_constructor:PbRequestVoteRequest)
}

void PbRequestVoteRequest::SharedCtor() {
  candidateid_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&term_, 0, static_cast<size_t>(
													reinterpret_cast<char *>(&lastlogterm_) -
													reinterpret_cast<char *>(&term_)) + sizeof(lastlogterm_));
}

PbRequestVoteRequest::~PbRequestVoteRequest() {
  // @@protoc_insertion_point(destructor:PbRequestVoteRequest)
  SharedDtor();
}

void PbRequestVoteRequest::SharedDtor() {
  candidateid_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void PbRequestVoteRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

const ::google::protobuf::Descriptor *PbRequestVoteRequest::descriptor() {
  ::protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const PbRequestVoteRequest &PbRequestVoteRequest::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_raft_5fpeer_2eproto::scc_info_PbRequestVoteRequest.base);
  return *internal_default_instance();
}


void PbRequestVoteRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:PbRequestVoteRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  candidateid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&term_, 0, static_cast<size_t>(
													reinterpret_cast<char *>(&lastlogterm_) -
													reinterpret_cast<char *>(&term_)) + sizeof(lastlogterm_));
  _internal_metadata_.Clear();
}

bool PbRequestVoteRequest::MergePartialFromCodedStream(
		::google::protobuf::io::CodedInputStream *input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:PbRequestVoteRequest)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int64 term = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
							input, &term_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// string candidateId = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
							input, this->mutable_candidateid()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
							this->candidateid().data(), static_cast<int>(this->candidateid().length()),
							::google::protobuf::internal::WireFormatLite::PARSE,
							"PbRequestVoteRequest.candidateId"));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// int64 lastLogIndex = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
							input, &lastlogindex_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// int64 lastLogTerm = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(32u /* 32 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
							input, &lastlogterm_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
				handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
						input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
	success:
  // @@protoc_insertion_point(parse_success:PbRequestVoteRequest)
  return true;
	failure:
  // @@protoc_insertion_point(parse_failure:PbRequestVoteRequest)
  return false;
#undef DO_
}

void PbRequestVoteRequest::SerializeWithCachedSizes(
		::google::protobuf::io::CodedOutputStream *output) const {
  // @@protoc_insertion_point(serialize_start:PbRequestVoteRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 term = 1;
  if (this->term() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->term(), output);
  }

  // string candidateId = 2;
  if (this->candidateid().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->candidateid().data(), static_cast<int>(this->candidateid().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbRequestVoteRequest.candidateId");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
				2, this->candidateid(), output);
  }

  // int64 lastLogIndex = 3;
  if (this->lastlogindex() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(3, this->lastlogindex(), output);
  }

  // int64 lastLogTerm = 4;
  if (this->lastlogterm() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(4, this->lastlogterm(), output);
  }

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				output);
  }
  // @@protoc_insertion_point(serialize_end:PbRequestVoteRequest)
}

::google::protobuf::uint8 *PbRequestVoteRequest::InternalSerializeWithCachedSizesToArray(
		bool deterministic, ::google::protobuf::uint8 *target) const {
	(void) deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:PbRequestVoteRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 term = 1;
  if (this->term() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->term(), target);
  }

  // string candidateId = 2;
  if (this->candidateid().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
				this->candidateid().data(), static_cast<int>(this->candidateid().length()),
				::google::protobuf::internal::WireFormatLite::SERIALIZE,
				"PbRequestVoteRequest.candidateId");
    target =
				::google::protobuf::internal::WireFormatLite::WriteStringToArray(
						2, this->candidateid(), target);
  }

  // int64 lastLogIndex = 3;
  if (this->lastlogindex() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(3, this->lastlogindex(), target);
  }

  // int64 lastLogTerm = 4;
  if (this->lastlogterm() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(4, this->lastlogterm(), target);
  }

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PbRequestVoteRequest)
  return target;
}

size_t PbRequestVoteRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PbRequestVoteRequest)
  size_t total_size = 0;

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
				::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
						(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																							: _internal_metadata_.default_instance()));
  }
  // string candidateId = 2;
  if (this->candidateid().size() > 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::StringSize(
											this->candidateid());
  }

  // int64 term = 1;
  if (this->term() != 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::Int64Size(
											this->term());
  }

  // int64 lastLogIndex = 3;
  if (this->lastlogindex() != 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::Int64Size(
											this->lastlogindex());
  }

  // int64 lastLogTerm = 4;
  if (this->lastlogterm() != 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::Int64Size(
											this->lastlogterm());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void PbRequestVoteRequest::MergeFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_merge_from_start:PbRequestVoteRequest)
			GOOGLE_DCHECK_NE(&from, this);
	const PbRequestVoteRequest *source =
      ::google::protobuf::internal::DynamicCastToGenerated<const PbRequestVoteRequest>(
          &from);
  if (source == NULL) {
		// @@protoc_insertion_point(generalized_merge_from_cast_fail:PbRequestVoteRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
		// @@protoc_insertion_point(generalized_merge_from_cast_success:PbRequestVoteRequest)
    MergeFrom(*source);
  }
}

void PbRequestVoteRequest::MergeFrom(const PbRequestVoteRequest &from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PbRequestVoteRequest)
			GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.candidateid().size() > 0) {

    candidateid_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.candidateid_);
  }
  if (from.term() != 0) {
    set_term(from.term());
  }
  if (from.lastlogindex() != 0) {
    set_lastlogindex(from.lastlogindex());
  }
  if (from.lastlogterm() != 0) {
    set_lastlogterm(from.lastlogterm());
  }
}

void PbRequestVoteRequest::CopyFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_copy_from_start:PbRequestVoteRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PbRequestVoteRequest::CopyFrom(const PbRequestVoteRequest &from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PbRequestVoteRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PbRequestVoteRequest::IsInitialized() const {
  return true;
}

void PbRequestVoteRequest::Swap(PbRequestVoteRequest *other) {
  if (other == this) return;
  InternalSwap(other);
}

void PbRequestVoteRequest::InternalSwap(PbRequestVoteRequest *other) {
  using std::swap;
  candidateid_.Swap(&other->candidateid_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
										GetArenaNoVirtual());
  swap(term_, other->term_);
  swap(lastlogindex_, other->lastlogindex_);
  swap(lastlogterm_, other->lastlogterm_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata PbRequestVoteRequest::GetMetadata() const {
  protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

void PbRequestVoteResponse::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int PbRequestVoteResponse::kTermFieldNumber;
const int PbRequestVoteResponse::kVoteGrantedFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

PbRequestVoteResponse::PbRequestVoteResponse()
		: ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_raft_5fpeer_2eproto::scc_info_PbRequestVoteResponse.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:PbRequestVoteResponse)
}

PbRequestVoteResponse::PbRequestVoteResponse(const PbRequestVoteResponse &from)
		: ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&term_, &from.term_,
					 static_cast<size_t>(reinterpret_cast<char *>(&votegranted_) -
															 reinterpret_cast<char *>(&term_)) + sizeof(votegranted_));
  // @@protoc_insertion_point(copy_constructor:PbRequestVoteResponse)
}

void PbRequestVoteResponse::SharedCtor() {
  ::memset(&term_, 0, static_cast<size_t>(
													reinterpret_cast<char *>(&votegranted_) -
													reinterpret_cast<char *>(&term_)) + sizeof(votegranted_));
}

PbRequestVoteResponse::~PbRequestVoteResponse() {
  // @@protoc_insertion_point(destructor:PbRequestVoteResponse)
  SharedDtor();
}

void PbRequestVoteResponse::SharedDtor() {
}

void PbRequestVoteResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

const ::google::protobuf::Descriptor *PbRequestVoteResponse::descriptor() {
  ::protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const PbRequestVoteResponse &PbRequestVoteResponse::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_raft_5fpeer_2eproto::scc_info_PbRequestVoteResponse.base);
  return *internal_default_instance();
}


void PbRequestVoteResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:PbRequestVoteResponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&term_, 0, static_cast<size_t>(
													reinterpret_cast<char *>(&votegranted_) -
													reinterpret_cast<char *>(&term_)) + sizeof(votegranted_));
  _internal_metadata_.Clear();
}

bool PbRequestVoteResponse::MergePartialFromCodedStream(
		::google::protobuf::io::CodedInputStream *input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:PbRequestVoteResponse)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int64 term = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
							input, &term_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

				// bool voteGranted = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
							bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
							input, &votegranted_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
				handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
						input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
	success:
  // @@protoc_insertion_point(parse_success:PbRequestVoteResponse)
  return true;
	failure:
  // @@protoc_insertion_point(parse_failure:PbRequestVoteResponse)
  return false;
#undef DO_
}

void PbRequestVoteResponse::SerializeWithCachedSizes(
		::google::protobuf::io::CodedOutputStream *output) const {
  // @@protoc_insertion_point(serialize_start:PbRequestVoteResponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 term = 1;
  if (this->term() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(1, this->term(), output);
  }

  // bool voteGranted = 2;
  if (this->votegranted() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->votegranted(), output);
  }

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				output);
  }
  // @@protoc_insertion_point(serialize_end:PbRequestVoteResponse)
}

::google::protobuf::uint8 *PbRequestVoteResponse::InternalSerializeWithCachedSizesToArray(
		bool deterministic, ::google::protobuf::uint8 *target) const {
	(void) deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:PbRequestVoteResponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 term = 1;
  if (this->term() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(1, this->term(), target);
  }

  // bool voteGranted = 2;
  if (this->votegranted() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->votegranted(), target);
  }

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
				(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																					: _internal_metadata_.default_instance()),
				target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:PbRequestVoteResponse)
  return target;
}

size_t PbRequestVoteResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:PbRequestVoteResponse)
  size_t total_size = 0;

	if ((_internal_metadata_.have_unknown_fields() && ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
				::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
						(::google::protobuf::internal::GetProto3PreserveUnknownsDefault() ? _internal_metadata_.unknown_fields()
																																							: _internal_metadata_.default_instance()));
  }
  // int64 term = 1;
  if (this->term() != 0) {
    total_size += 1 +
									::google::protobuf::internal::WireFormatLite::Int64Size(
											this->term());
  }

  // bool voteGranted = 2;
  if (this->votegranted() != 0) {
    total_size += 1 + 1;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void PbRequestVoteResponse::MergeFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_merge_from_start:PbRequestVoteResponse)
			GOOGLE_DCHECK_NE(&from, this);
	const PbRequestVoteResponse *source =
      ::google::protobuf::internal::DynamicCastToGenerated<const PbRequestVoteResponse>(
          &from);
  if (source == NULL) {
		// @@protoc_insertion_point(generalized_merge_from_cast_fail:PbRequestVoteResponse)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
		// @@protoc_insertion_point(generalized_merge_from_cast_success:PbRequestVoteResponse)
    MergeFrom(*source);
  }
}

void PbRequestVoteResponse::MergeFrom(const PbRequestVoteResponse &from) {
// @@protoc_insertion_point(class_specific_merge_from_start:PbRequestVoteResponse)
			GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.term() != 0) {
    set_term(from.term());
  }
  if (from.votegranted() != 0) {
    set_votegranted(from.votegranted());
  }
}

void PbRequestVoteResponse::CopyFrom(const ::google::protobuf::Message &from) {
// @@protoc_insertion_point(generalized_copy_from_start:PbRequestVoteResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PbRequestVoteResponse::CopyFrom(const PbRequestVoteResponse &from) {
// @@protoc_insertion_point(class_specific_copy_from_start:PbRequestVoteResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PbRequestVoteResponse::IsInitialized() const {
  return true;
}

void PbRequestVoteResponse::Swap(PbRequestVoteResponse *other) {
  if (other == this) return;
  InternalSwap(other);
}

void PbRequestVoteResponse::InternalSwap(PbRequestVoteResponse *other) {
  using std::swap;
  swap(term_, other->term_);
  swap(votegranted_, other->votegranted_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata PbRequestVoteResponse::GetMetadata() const {
  protobuf_raft_5fpeer_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_raft_5fpeer_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
namespace google {
	namespace protobuf {
		template<>
		GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::PbPutRequest *Arena::CreateMaybeMessage<::PbPutRequest>(Arena *arena) {
			return Arena::CreateInternal<::PbPutRequest>(arena);
		}

		template<>
		GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::PbPutResponse *Arena::CreateMaybeMessage<::PbPutResponse>(Arena *arena) {
			return Arena::CreateInternal<::PbPutResponse>(arena);
		}

		template<>
		GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::PbAppendEntriesRequest_Entry *
		Arena::CreateMaybeMessage<::PbAppendEntriesRequest_Entry>(Arena *arena) {
			return Arena::CreateInternal<::PbAppendEntriesRequest_Entry>(arena);
		}

		template<>
		GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::PbAppendEntriesRequest *
		Arena::CreateMaybeMessage<::PbAppendEntriesRequest>(Arena *arena) {
			return Arena::CreateInternal<::PbAppendEntriesRequest>(arena);
		}

		template<>
		GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::PbAppendEntriesResponse *
		Arena::CreateMaybeMessage<::PbAppendEntriesResponse>(Arena *arena) {
			return Arena::CreateInternal<::PbAppendEntriesResponse>(arena);
		}

		template<>
		GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::PbRequestVoteRequest *
		Arena::CreateMaybeMessage<::PbRequestVoteRequest>(Arena *arena) {
			return Arena::CreateInternal<::PbRequestVoteRequest>(arena);
		}

		template<>
		GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::PbRequestVoteResponse *
		Arena::CreateMaybeMessage<::PbRequestVoteResponse>(Arena *arena) {
			return Arena::CreateInternal<::PbRequestVoteResponse>(arena);
		}
	}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
