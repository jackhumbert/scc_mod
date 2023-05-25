#pragma once

namespace red {

struct String {

  inline bool IsInline() const noexcept { return length < 0x40000000; }

  inline uint32_t Length() const noexcept { return length & 0x3FFFFFFF; }

  inline const char *c_str() const noexcept {
    if (IsInline()) {
      return text.inline_str;
    }

    return text.str.ptr;
  }

  inline bool operator==(const char *aRhs) const noexcept {
    auto lhsText = c_str();
    if (!lhsText || !aRhs) {
      return false;
    }

    return strcmp(lhsText, aRhs) == 0;
  }

  inline bool operator==(const String &aRhs) const noexcept {
    auto lhsText = c_str();
    if (!lhsText) {
      return false;
    }
    auto rhsText = aRhs.c_str();
    if (!rhsText) {
      return false;
    }

    if (Length() != aRhs.Length()) {
      return false;
    }

    return strcmp(lhsText, rhsText) == 0;
  }

#pragma pack(push, 4)
  union {
    char inline_str[0x14];
    struct {
      char *ptr;
      int8_t unk[8];
      int32_t capacity;
    } str;
  } text; // 00
#pragma pack(pop)
  uint32_t length;
  uint64_t allocator;
};

} // namespace red