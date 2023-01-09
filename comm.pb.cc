// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: comm.proto

#include "comm.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace server {
PROTOBUF_CONSTEXPR Player::Player(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_._has_bits_)*/{}
  , /*decltype(_impl_._cached_size_)*/{}
  , /*decltype(_impl_.username_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.life_)*/0
  , /*decltype(_impl_.attack_)*/0} {}
struct PlayerDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PlayerDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PlayerDefaultTypeInternal() {}
  union {
    Player _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PlayerDefaultTypeInternal _Player_default_instance_;
}  // namespace server
static ::_pb::Metadata file_level_metadata_comm_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_comm_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_comm_2eproto = nullptr;

const uint32_t TableStruct_comm_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::server::Player, _impl_._has_bits_),
  PROTOBUF_FIELD_OFFSET(::server::Player, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::server::Player, _impl_.username_),
  PROTOBUF_FIELD_OFFSET(::server::Player, _impl_.life_),
  PROTOBUF_FIELD_OFFSET(::server::Player, _impl_.attack_),
  0,
  1,
  2,
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 9, -1, sizeof(::server::Player)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::server::_Player_default_instance_._instance,
};

const char descriptor_table_protodef_comm_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\ncomm.proto\022\006server\"h\n\006Player\022\025\n\010userna"
  "me\030\001 \001(\tH\000\210\001\001\022\021\n\004life\030\002 \001(\005H\001\210\001\001\022\023\n\006atta"
  "ck\030\003 \001(\005H\002\210\001\001B\013\n\t_usernameB\007\n\005_lifeB\t\n\007_"
  "attackb\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_comm_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_comm_2eproto = {
    false, false, 134, descriptor_table_protodef_comm_2eproto,
    "comm.proto",
    &descriptor_table_comm_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_comm_2eproto::offsets,
    file_level_metadata_comm_2eproto, file_level_enum_descriptors_comm_2eproto,
    file_level_service_descriptors_comm_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_comm_2eproto_getter() {
  return &descriptor_table_comm_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_comm_2eproto(&descriptor_table_comm_2eproto);
namespace server {

// ===================================================================

class Player::_Internal {
 public:
  using HasBits = decltype(std::declval<Player>()._impl_._has_bits_);
  static void set_has_username(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_life(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_attack(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
};

Player::Player(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:server.Player)
}
Player::Player(const Player& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Player* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){from._impl_._has_bits_}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.username_){}
    , decltype(_impl_.life_){}
    , decltype(_impl_.attack_){}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.username_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.username_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (from._internal_has_username()) {
    _this->_impl_.username_.Set(from._internal_username(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.life_, &from._impl_.life_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.attack_) -
    reinterpret_cast<char*>(&_impl_.life_)) + sizeof(_impl_.attack_));
  // @@protoc_insertion_point(copy_constructor:server.Player)
}

inline void Player::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_._has_bits_){}
    , /*decltype(_impl_._cached_size_)*/{}
    , decltype(_impl_.username_){}
    , decltype(_impl_.life_){0}
    , decltype(_impl_.attack_){0}
  };
  _impl_.username_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.username_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

Player::~Player() {
  // @@protoc_insertion_point(destructor:server.Player)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Player::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.username_.Destroy();
}

void Player::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Player::Clear() {
// @@protoc_insertion_point(message_clear_start:server.Player)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    _impl_.username_.ClearNonDefaultToEmpty();
  }
  if (cached_has_bits & 0x00000006u) {
    ::memset(&_impl_.life_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&_impl_.attack_) -
        reinterpret_cast<char*>(&_impl_.life_)) + sizeof(_impl_.attack_));
  }
  _impl_._has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Player::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional string username = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_username();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "server.Player.username"));
        } else
          goto handle_unusual;
        continue;
      // optional int32 life = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _Internal::set_has_life(&has_bits);
          _impl_.life_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // optional int32 attack = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 24)) {
          _Internal::set_has_attack(&has_bits);
          _impl_.attack_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  _impl_._has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Player::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:server.Player)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // optional string username = 1;
  if (_internal_has_username()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_username().data(), static_cast<int>(this->_internal_username().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "server.Player.username");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_username(), target);
  }

  // optional int32 life = 2;
  if (_internal_has_life()) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_life(), target);
  }

  // optional int32 attack = 3;
  if (_internal_has_attack()) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(3, this->_internal_attack(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:server.Player)
  return target;
}

size_t Player::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:server.Player)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _impl_._has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    // optional string username = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
          this->_internal_username());
    }

    // optional int32 life = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_life());
    }

    // optional int32 attack = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_attack());
    }

  }
  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Player::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Player::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Player::GetClassData() const { return &_class_data_; }


void Player::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Player*>(&to_msg);
  auto& from = static_cast<const Player&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:server.Player)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._impl_._has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    if (cached_has_bits & 0x00000001u) {
      _this->_internal_set_username(from._internal_username());
    }
    if (cached_has_bits & 0x00000002u) {
      _this->_impl_.life_ = from._impl_.life_;
    }
    if (cached_has_bits & 0x00000004u) {
      _this->_impl_.attack_ = from._impl_.attack_;
    }
    _this->_impl_._has_bits_[0] |= cached_has_bits;
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Player::CopyFrom(const Player& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:server.Player)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Player::IsInitialized() const {
  return true;
}

void Player::InternalSwap(Player* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_._has_bits_[0], other->_impl_._has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.username_, lhs_arena,
      &other->_impl_.username_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Player, _impl_.attack_)
      + sizeof(Player::_impl_.attack_)
      - PROTOBUF_FIELD_OFFSET(Player, _impl_.life_)>(
          reinterpret_cast<char*>(&_impl_.life_),
          reinterpret_cast<char*>(&other->_impl_.life_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Player::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_comm_2eproto_getter, &descriptor_table_comm_2eproto_once,
      file_level_metadata_comm_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace server
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::server::Player*
Arena::CreateMaybeMessage< ::server::Player >(Arena* arena) {
  return Arena::CreateMessageInternal< ::server::Player >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
