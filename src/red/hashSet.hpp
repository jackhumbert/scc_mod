#pragma once

#include "pool.hpp"

namespace red {

template <typename TElement> struct HashSet {

  struct Hash {
    uint32_t m_hash;
    uint32_t m_index;
    uint32_t m_next;
  };

  TElement *m_buffer;                       // 00
  Hash *m_hashes;                           // 08
  uint32_t m_size;                          // 10
  uint32_t m_capacity;                      // 14
  Pool<PoolEntry<uint32_t, uint32_t>> pool; // 18
  uintptr_t allocator;
};

static_assert(sizeof(HashSet<uint32_t>) == 0x38);

} // namespace red