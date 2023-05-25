#pragma once

#include "dynamicBuffer.hpp"

namespace red {

#pragma pack(push, 4)

template <typename T> struct DynArray : DynamicBuffer<T> {

  const T &operator[](uint32_t aIndex) const { return this->m_buffer[aIndex]; }

#pragma region Iterator
  T *Begin() { return this->m_buffer; }

  const T *Begin() const { return this->m_buffer; }

  T *begin() { return Begin(); }

  const T *begin() const { return Begin(); }

  T *End() { return this->m_buffer + m_size; }

  const T *End() const { return this->m_buffer + m_size; }

  T *end() { return End(); }

  const T *end() const { return End(); }
#pragma endregion

  uint32_t m_size;
};

static_assert(sizeof(DynArray<uint32_t>) == 0x10);

#pragma pack(pop)

} // namespace red