#pragma once

namespace red {

#pragma pack(push, 4)

template <typename T> struct DynamicBuffer {
  T *m_buffer;
  uint32_t m_capacity;
};

static_assert(sizeof(DynamicBuffer<uint32_t>) == 0x0C);

#pragma pack(pop)

} // namespace red