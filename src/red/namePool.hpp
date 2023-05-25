#pragma once

#include "name.hpp"

namespace red {

struct NamePoolEntry {
  uint8_t length;
  uint64_t unk08;
  uint64_t unk10;
  uint64_t unk18;
  const char *str;
};

struct NamePool {
  constexpr const static uintptr_t Addr = 0x81D980;

  uint64_t unk00;
  uint64_t unk08;
  NamePoolEntry *entry;
  uint64_t unk18;
  uint64_t unk20;
  uint64_t unk28;
  uint64_t unk30;
  uint64_t unk38;
  uint32_t unk40;
  uint32_t unk44 = 3;
};

struct NamePoolLookup {
  constexpr const static uintptr_t Addr = 0x41D940;

  uint8_t lock;
  NamePool *pool;
  uint32_t unk10;
  uint32_t unk14;
  Name *lookup;
};

} // namespace red