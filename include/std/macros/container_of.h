#pragma once

#define container_of(ptr, type, member) container_of_impl(ptr, type, member)
#define container_of_impl(ptr, type, member)                   \
    ({                                                         \
        void *__mptr = (void *)(ptr);                          \
        ((type *)(__mptr - __builtin_offsetof(type, member))); \
    })
