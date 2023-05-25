#pragma once

#include "pool.hpp"

namespace red {

template <typename K, typename T> struct HashMap {
  static const uint32_t INVALID_INDEX = static_cast<uint32_t>(-1);

  struct Iterator {
    Iterator(HashMap &hashMap) : m_hashMap(hashMap) {
      uint32_t index, i = 0;
      if (hashMap->m_size) {
        if (hashMap->m_capacity) {
          while (1) {
            index = hashMap->indexTable[i];
            if (index != -1)
              break;
            this->m_index = ++i;
            if (i >= hashMap->m_capacity)
              return this;
          }
          this->m_element = hashMap->pool.GetElement(index);
        }
      } else {
        this->m_index = hashMap->m_capacity;
      }
    }

    inline void Next() {
      if (m_index < m_hashMap->m_capacity) {
        auto element = m_element->m_next;
        if (element == -1) {
          auto i = m_index + 1;
          m_index = i;
          if (i >= m_hashMap->m_capacity) {
          LABEL_9:
            m_element = 0i64;
            return;
          }
          while (1) {
            element = m_hashMap->indexTable[i];
            if (element != -1)
              break;
            i = (i + 1);
            m_index = i;
            if (i >= m_hashMap->m_capacity)
              goto LABEL_9;
          }
        }
        m_element = m_hashMap->pool.GetElement(element);
      }
    }

    HashMap *m_hashMap;         // 00
    uint32_t m_index;           // 08
    PoolEntry<K, T> *m_element; // 10
    bool created;               // 18
  };

  static_assert(sizeof(Iterator) == 0x20);

  inline PoolEntry<K, T> *CreateNewElement(K key) {
    auto entry = m_pool.CreateNewElement();
    ASSERT(entry, "");
    entry->key = key;
    return entry;
  }

  uint32_t *indexTable;         // 00
  uint32_t m_size;              // 08
  uint32_t m_capacity;          // 0C
  Pool<PoolEntry<K, T>> m_pool; // 10
  uintptr_t allocator;          // 28
};

static_assert(sizeof(HashMap<uint32_t, void *>) == 0x30);

} // namespace red