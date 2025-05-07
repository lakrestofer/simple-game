#pragma once
// some commonly used clib types
#include <stddef.h>

#define Slice(type) \
    struct {        \
        type* data; \
        size_t len; \
    }
