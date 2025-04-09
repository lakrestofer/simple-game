#ifndef TYPES_H_DEFINED
#define TYPES_H_DEFINED

#include <stddef.h>

#define Slice(type) \
  struct {          \
    type* data;     \
    size_t len;     \
  }

#endif  // TYPES_H_DEFINED
