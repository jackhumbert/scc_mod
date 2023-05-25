#include "name.hpp"

const char *red::Name::ToString() const {
  auto call = reinterpret_cast<const char *(*)(const Name *)>(
      0x556A0 + GetBaseAddress());
  return call(this);
}