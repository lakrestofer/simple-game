#pragma once

#include <stddef.h>

static inline size_t align_up(size_t address, size_t alignment) {
    return (address + alignment - 1) & !(alignment - 1);
}
