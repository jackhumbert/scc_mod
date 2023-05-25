// #include "pool.hpp"
// #include "utility.hpp"









































// template <>
// uint32_t red::Pool<void>::Create(void * buffer, uint32_t bufferSize, uint32_t blockSize) {
//   ASSERT(( reinterpret_cast< uintptr_t >( buffer ) & 3 ) == 0);
//   ASSERT(( blockSize & 3 ) == 0);
//   ASSERT(blockSize >= 4);
//   ASSERT(buffer != nullptr || bufferSize == 0);
//   return true;
//  }



































































// template<>
// bool red::Pool<void>::BelongsToPool(uintptr_t block) {
//   ASSERT((uintptr_t)m_buffer <= block && block < red::OffsetPtr( m_buffer, DataCapacity() ));
//   return true;
// }


