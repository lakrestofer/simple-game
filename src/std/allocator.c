#include "std/mem/allocator.h"

/// Create allocator vtable
AllocatorVTable allocatorVtableNew(
    AllocFn alloc,
    AllocFn alloc_nonzeroed,
    AllocAlignedFn alloc_aligned,
    AllocAlignedFn alloc_nonzeroed_aligned,
    DeallocFn dealloc
) {
    return (AllocatorVTable){
        alloc,
        alloc_nonzeroed,
        alloc_aligned,
        alloc_nonzeroed_aligned,
        dealloc,
    };
}
/// Create allocator
Allocator allocatorNew(void* const data, AllocatorVTable* const vtable) {
    return (Allocator){data, vtable};
}
/// Allocate memory. Zeroes memory. Does not align address
void* alloc(Allocator* allocator, size_t size) {
    return allocator->vtable->alloc(allocator->data, size);
}
/// Allocate memory. Does not zero memory. Does not align address
void* allocNonZeroed(Allocator* allocator, size_t size) {
    return allocator->vtable->alloc_nonzeroed(allocator->data, size);
}
/// Allocate memory. Zeroes memory. Aligns address
void* allocAligned(Allocator* allocator, size_t size, size_t alignment) {
    return allocator->vtable->alloc_aligned(allocator->data, size, alignment);
}
/// Allocate memory. Does not zero memory. Aligns address
void* allocNonZeroedAligned(
    Allocator* allocator, size_t size, size_t alignment
) {
    return allocator->vtable->alloc_nonzeroed_aligned(
        allocator->data, size, alignment
    );
}
/// Deallocates memory
void dealloc(Allocator* allocator, void* ptr) {
    return allocator->vtable->dealloc(allocator->data, ptr);
}
