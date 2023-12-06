#pragma once

#include "utility.hpp"

namespace red {
  
struct Name {
  /// @pattern 48 83 EC 38 48 8B 11 48 8D 4C 24 20 E8 ? ? ? ? 48 8B 00 48 83 C4 38 C3
  /// @rva 0x556A0
  /// @rva 0x63790
  const char *ToString() const;

  uint64_t hash;
};

} // namespace red