#pragma once

#include "dynArray.hpp"

namespace red {

struct PoolRegistry {

  struct Info {
    uint64_t unk00;
    uint64_t unk08;
    uint64_t storage;
    uint64_t unk18;
    uint64_t unk20;
    uint64_t unk28;
    uint64_t unk30;
    uint64_t unk38;
    uint64_t unk40;
    uint32_t key;
  };

  std::mutex mutex;
  Info *nodes[0x1E00];
  uint32_t unkF008;
  uint32_t unkF00C;
  uint64_t unkF010[2304];
  uint64_t unk13810[8];
  uint64_t unk13850;
  uint64_t unk13858;
  uint64_t unk13860;
};

} // namespace red