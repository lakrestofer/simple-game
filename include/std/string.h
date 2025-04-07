#ifndef STRING_H_DEFINED
#define STRING_H_DEFINED

#include <stddef.h>

#define Slice(type) \
  struct {          \
    type* data;     \
    size_t len;     \
  }

typedef struct {
  char* data;
  size_t len;
} String;

#endif  // STRING_H_DEFINED
