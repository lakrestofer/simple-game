#pragma once
// internal imports

// external imports
#include <stddef.h>

typedef struct Allocator Allocator;
typedef struct AllocatorVTable AllocatorVTable;

// Typedefs for the function signatures
typedef void* (*AllocFn)(void* ctx, size_t size);
typedef void* (*AllocAlignedFn)(void* ctx, size_t size, size_t alignment);
typedef void (*DeallocFn)(void* ctx, void* ptr);

/// VTable for  Allocator
struct AllocatorVTable {
    AllocFn alloc;
    AllocFn alloc_nonzeroed;
    AllocAlignedFn alloc_aligned;
    AllocAlignedFn alloc_nonzeroed_aligned;
    DeallocFn dealloc;
};

/// A generic allocator
struct Allocator {
    void* data;
    AllocatorVTable* vtable;
};

/// Create allocator vtable
AllocatorVTable allocatorVtableNew(
    AllocFn alloc_impl,
    AllocFn alloc_nonzeroed_impl,
    AllocAlignedFn alloc_aligned_impl,
    AllocAlignedFn alloc_nonzeroed_aligned_impl,
    DeallocFn dealloc_impl
);

/// Create allocator
Allocator allocatorNew(void* data, AllocatorVTable* vtable);

/// Allocate memory. Zeroes memory. Does not align address
void* alloc(Allocator* allocator, size_t size);
/// Allocate memory. Does not zero memory. Does not align address
void* allocNonZeroed(Allocator* allocator, size_t size);

/// Allocate memory. Zeroes memory. Aligns address
void* allocAligned(Allocator* allocator, size_t size, size_t alignment);
/// Allocate memory. Does not zero memory. Aligns address
void* allocNonZeroedAligned(
    Allocator* allocator, size_t size, size_t alignment
);

/// Deallocates memory
void dealloc(Allocator* allocator, void* ptr);
