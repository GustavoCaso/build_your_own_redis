#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>
#include <stddef.h>

template <class P, class M>
size_t my_offsetof(const M P::*member)
{
  return (size_t) & (reinterpret_cast<P *>(0)->*member);
}

template <class P, class M>
P *my_container_of_impl(M *ptr, const M P::*member)
{
  return (P *)((char *)ptr - my_offsetof(member));
}

#define container_of(ptr, type, member) \
  my_container_of_impl(ptr, &type::member)

inline uint64_t str_hash(const uint8_t *data, size_t len)
{
  uint32_t h = 0x811C9DC5;
  for (size_t i = 0; i < len; i++)
  {
    h = (h + data[i]) * 0x01000193;
  }
  return h;
}

enum
{
  SER_NIL = 0,
  SER_ERR = 1,
  SER_STR = 2,
  SER_INT = 3,
  SER_DBL = 4,
  SER_ARR = 5,
};

#endif
