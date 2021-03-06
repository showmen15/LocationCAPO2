// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ArucoLocation.proto

#ifndef PROTOBUF_ArucoLocation_2eproto__INCLUDED
#define PROTOBUF_ArucoLocation_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace Aruco {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_ArucoLocation_2eproto();
void protobuf_AssignDesc_ArucoLocation_2eproto();
void protobuf_ShutdownFile_ArucoLocation_2eproto();

class ArucoLocation;

// ===================================================================

class ArucoLocation : public ::google::protobuf::Message {
 public:
  ArucoLocation();
  virtual ~ArucoLocation();

  ArucoLocation(const ArucoLocation& from);

  inline ArucoLocation& operator=(const ArucoLocation& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ArucoLocation& default_instance();

  void Swap(ArucoLocation* other);

  // implements Message ----------------------------------------------

  ArucoLocation* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ArucoLocation& from);
  void MergeFrom(const ArucoLocation& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 RobotID = 1;
  inline bool has_robotid() const;
  inline void clear_robotid();
  static const int kRobotIDFieldNumber = 1;
  inline ::google::protobuf::int32 robotid() const;
  inline void set_robotid(::google::protobuf::int32 value);

  // required double X = 2;
  inline bool has_x() const;
  inline void clear_x();
  static const int kXFieldNumber = 2;
  inline double x() const;
  inline void set_x(double value);

  // required double Y = 3;
  inline bool has_y() const;
  inline void clear_y();
  static const int kYFieldNumber = 3;
  inline double y() const;
  inline void set_y(double value);

  // required double Alfa = 4;
  inline bool has_alfa() const;
  inline void clear_alfa();
  static const int kAlfaFieldNumber = 4;
  inline double alfa() const;
  inline void set_alfa(double value);

  // required int32 TimeStamp = 5;
  inline bool has_timestamp() const;
  inline void clear_timestamp();
  static const int kTimeStampFieldNumber = 5;
  inline ::google::protobuf::int32 timestamp() const;
  inline void set_timestamp(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Aruco.ArucoLocation)
 private:
  inline void set_has_robotid();
  inline void clear_has_robotid();
  inline void set_has_x();
  inline void clear_has_x();
  inline void set_has_y();
  inline void clear_has_y();
  inline void set_has_alfa();
  inline void clear_has_alfa();
  inline void set_has_timestamp();
  inline void clear_has_timestamp();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  double x_;
  double y_;
  ::google::protobuf::int32 robotid_;
  ::google::protobuf::int32 timestamp_;
  double alfa_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(5 + 31) / 32];

  friend void  protobuf_AddDesc_ArucoLocation_2eproto();
  friend void protobuf_AssignDesc_ArucoLocation_2eproto();
  friend void protobuf_ShutdownFile_ArucoLocation_2eproto();

  void InitAsDefaultInstance();
  static ArucoLocation* default_instance_;
};
// ===================================================================


// ===================================================================

// ArucoLocation

// required int32 RobotID = 1;
inline bool ArucoLocation::has_robotid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ArucoLocation::set_has_robotid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ArucoLocation::clear_has_robotid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ArucoLocation::clear_robotid() {
  robotid_ = 0;
  clear_has_robotid();
}
inline ::google::protobuf::int32 ArucoLocation::robotid() const {
  return robotid_;
}
inline void ArucoLocation::set_robotid(::google::protobuf::int32 value) {
  set_has_robotid();
  robotid_ = value;
}

// required double X = 2;
inline bool ArucoLocation::has_x() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ArucoLocation::set_has_x() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ArucoLocation::clear_has_x() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ArucoLocation::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline double ArucoLocation::x() const {
  return x_;
}
inline void ArucoLocation::set_x(double value) {
  set_has_x();
  x_ = value;
}

// required double Y = 3;
inline bool ArucoLocation::has_y() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ArucoLocation::set_has_y() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ArucoLocation::clear_has_y() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ArucoLocation::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline double ArucoLocation::y() const {
  return y_;
}
inline void ArucoLocation::set_y(double value) {
  set_has_y();
  y_ = value;
}

// required double Alfa = 4;
inline bool ArucoLocation::has_alfa() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void ArucoLocation::set_has_alfa() {
  _has_bits_[0] |= 0x00000008u;
}
inline void ArucoLocation::clear_has_alfa() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void ArucoLocation::clear_alfa() {
  alfa_ = 0;
  clear_has_alfa();
}
inline double ArucoLocation::alfa() const {
  return alfa_;
}
inline void ArucoLocation::set_alfa(double value) {
  set_has_alfa();
  alfa_ = value;
}

// required int32 TimeStamp = 5;
inline bool ArucoLocation::has_timestamp() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void ArucoLocation::set_has_timestamp() {
  _has_bits_[0] |= 0x00000010u;
}
inline void ArucoLocation::clear_has_timestamp() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void ArucoLocation::clear_timestamp() {
  timestamp_ = 0;
  clear_has_timestamp();
}
inline ::google::protobuf::int32 ArucoLocation::timestamp() const {
  return timestamp_;
}
inline void ArucoLocation::set_timestamp(::google::protobuf::int32 value) {
  set_has_timestamp();
  timestamp_ = value;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace Aruco

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ArucoLocation_2eproto__INCLUDED
