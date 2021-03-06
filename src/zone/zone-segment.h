// Copyright 2016 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_ZONE_ZONE_SEGMENT_H_
#define V8_ZONE_ZONE_SEGMENT_H_

#include "src/v8.h"

// Segments represent chunks of memory: They have starting address
// (encoded in the this pointer) and a size in bytes. Segments are
// chained together forming a LIFO structure with the newest segment
// available as segment_head_. Segments are allocated using malloc()
// and de-allocated using free().
namespace v8 {
namespace internal {

//  Forward declaration
class Zone;

class Segment {
 public:
  void Initialize(Segment* next, size_t size, Zone* zone) {
    next_ = next;
    size_ = size;
    zone_ = zone;
  }

  Zone* zone() const { return zone_; }
  void set_zone(Zone* const zone) { zone_ = zone; }

  Segment* next() const { return next_; }
  void set_next(Segment* const next) { next_ = next; }

  size_t size() const { return size_; }
  size_t capacity() const { return size_ - sizeof(Segment); }

  Address start() const { return address(sizeof(Segment)); }
  Address end() const { return address(size_); }

 private:
  // Computes the address of the nth byte in this segment.
  Address address(size_t n) const { return Address(this) + n; }

  Zone* zone_;
  Segment* next_;
  size_t size_;
};
}  // namespace internal
}  // namespace v8

#endif  // V8_ZONE_ZONE_SEGMENT_H_
