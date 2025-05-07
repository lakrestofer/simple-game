#pragma once

#include <stddef.h>
#include <stdbool.h>
#include "std/mem/allocator.h"

///////////////////////////////////////////////////////////////////////////////
// TYPE DEFINITION
///////////////////////////////////////////////////////////////////////////////

typedef struct {
    char* data;
    size_t size;
} String;

typedef struct {
    char* data;
    size_t size;
    size_t capacity;
    Allocator allocator;
} StringBuf;

typedef struct {
    String lhs;
    String rhs;
} SplitStringResult;

///////////////////////////////////////////////////////////////////////////////
// FUNCTION DEFINITION
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// private interface
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// public interface
// ----------------------------------------------------------------------------

#define stringNew(str) \
    __Generic((str), const char* : {str, sizeof(str) - 1})(str)

bool stringContains(String haystack, String needle);

String stringSlice(String, size_t start, size_t end);

SplitStringResult stringSplit(String string, size_t index);
String stringBufToString(StringBuf string);
