#pragma once

#include "dynamicBuffer.hpp"
#include "utility.hpp"

namespace red {

template <typename K, typename T> struct PoolEntry {
  uint32_t m_next;
  uint32_t m_hash;
  K key;
  T value;
};

static_assert(sizeof(PoolEntry<uint64_t, uint64_t>) == 0x18);

template <typename T> struct Pool : public DynamicBuffer<T> {
  uint32_t Create(void *buffer, uint32_t bufferSize, uint32_t blockSize);
  bool BelongsToPool(uintptr_t block);
  T* CreateNewElement();
  uint64_t GetIndexForBlock(uintptr_t block);

  inline T* GetElement(uint32_t index) {
    ASSERT(index < this->m_capacity, "Index out of bounds");
    return this->m_buffer + m_blockSize * index;
  }

  inline uint32_t DataCapacity() { return this->m_capacity * m_blockSize; }

  inline uint32_t GetIndex(void * block) {
    auto buffer = this->m_buffer;
    ASSERT(buffer <= block && block < red::OffsetPtr(buffer, DataCapacity()), "Block doesn't belong to the pool");
    auto diff = ByteDistance(block, buffer);
    return diff / m_blockSize;
  }

  uint32_t m_blockSize;  // 0C
  uint32_t m_next;       // 10
  uint32_t m_bufferSize; // 14
};

static_assert(sizeof(Pool<uint32_t>) == 0x18);

} // namespace red