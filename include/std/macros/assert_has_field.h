#ifndef ASSERT_HAS_FIELD_H_DEFINED
#define ASSERT_HAS_FIELD_H_DEFINED

#include "stddef.h"

#define STATIC_ASSERT_HAS_FIELD(type, field)       \
    _Static_assert(                                \
        sizeof((void)offsetof(type, field), char), \
        "Type " #type " must have field " #field   \
    )

#endif
