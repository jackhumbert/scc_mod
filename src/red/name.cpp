#include "name.hpp"

const char *red::Name::ToString() const {
  auto call = reinterpret_cast<const char *(*)(const Name *)>(
      0x63790 + GetBaseAddress());
  return call(this);
}