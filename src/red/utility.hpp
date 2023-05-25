#pragma once

#define ASSERT(expr, msg) if (!(expr)) { \
__debugbreak(); \
}

namespace red {

inline uintptr_t OffsetPtr(void * ptr, uint64_t offset) {
  return (uintptr_t)ptr + offset;
}

inline uintptr_t ByteDistance(void * a, void* b) {
    auto diff = (uintptr_t)a - (uintptr_t)b;
    ASSERT(diff >= 0 && diff <= 0xFFFFFFFF, "ByteDistance cannot store value in specified type.")
    return diff;
}

inline const uintptr_t GetBaseAddress() { return reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)); }

}