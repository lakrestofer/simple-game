#include "std/arena.h"
#include <string.h>
#include <assert.h>
#include "std/allocator.h"

#define ARENA_REGION_DEFAULT_CAPACITY (8 * 1024)

// ----------------------------------------------------------------------------
// life cycle
// ----------------------------------------------------------------------------

/// Create an arena
Arena arenaNew(Allocator child_allocator) {
    return (Arena){
        .start = NULL,
        .end = NULL,
        .child_allocator = child_allocator,
    };
}

/// Allocate a region
ArenaRegion* arenaRegionCreate(Allocator* allocator, size_t size) {
    ArenaRegion* region = alloc(allocator, sizeof(ArenaRegion) + size);
    return region;
}
/// deallocate a region
void arenaRegionDestroy(ArenaRegion* region, Allocator* allocator) {
    dealloc(allocator, region);
}

// ----------------------------------------------------------------------------
// query functions
// ----------------------------------------------------------------------------

/// current memory usage of the arena,
/// not including memory used by implementation
size_t arenaMemoryUsage();

// ----------------------------------------------------------------------------
// memory management (non `Allocator` api)
// ----------------------------------------------------------------------------

/// allocate memory
void* arenaAlloc(Arena* a, size_t size) {
    void* result = arenaAllocNonZeroed(a, size);
    memset(result, 0, size);
    return result;
}

void* arenaAllocNonZeroed(Arena* a, size_t size) {
    // init fresh arena
    if (a->end == NULL) {
        size_t capacity = (size_t)ARENA_REGION_DEFAULT_CAPACITY;
        if (capacity < size) capacity = size;
        a->end = a->start = arenaRegionCreate(&a->child_allocator, capacity);
    }
    // search for region with enough space
    while (a->end->size + size > a->end->capacity && a->end->next != NULL) {
        a->end = a->end->next;
    }
    // create new region if not
    if (a->end->size + size > a->end->capacity) {
        size_t capacity = (size_t)ARENA_REGION_DEFAULT_CAPACITY;
        if (capacity < size) capacity = size;
        a->end->next = a->end = arenaRegionCreate(
            &a->child_allocator, capacity
        );
    }
    // create and return pointer
    void* result = &a->end->data[a->end->size];
    a->end->size += size;
    return result;
}

/// resets an arena, freeing all the memory used
void arenaResetFree(Arena* arena) {
    ArenaRegion* r = arena->start;
    while (r != NULL) {
        ArenaRegion* temp = r;
        r = r->next;
        arenaRegionDestroy(temp, &arena->child_allocator);
    }
    arena->start = NULL;
    arena->end = NULL;
}

/// resets an arena, freeing all memory, then allocates a large enough
/// buffer to contain all previous allocations
void arenaResetRetain(Arena* arena) {
    ArenaRegion* r = arena->start;
    size_t new_capacity = 0;
    while (r != NULL) {
        ArenaRegion* temp = r;
        r = r->next;
        new_capacity += temp->size;
        arenaRegionDestroy(temp, &arena->child_allocator);
    }
    arena->start = arena->end = arenaRegionCreate(
        &arena->child_allocator, new_capacity
    );
}

/// resets an arena, freeing all memory, then allocates a large enough
/// buffer to contain all previous allocations, up to a limit
void arenaResetRetainWithLimit(Arena* arena, size_t limit) {
    ArenaRegion* r = arena->start;
    size_t new_capacity = 0;
    while (r != NULL) {
        ArenaRegion* temp = r;
        r = r->next;
        new_capacity += temp->size;
        arenaRegionDestroy(temp, &arena->child_allocator);
    }
    if (new_capacity > limit) new_capacity = limit;
    arena->start = arena->end = arenaRegionCreate(
        &arena->child_allocator, new_capacity
    );
}

static void* allocImpl(void* ctx, size_t size) {
    return arenaAlloc((Arena*)ctx, size);
}
static void* allocNonZeroedImpl(void* ctx, size_t size) {}
static void* allocAlignedImpl(void* ctx, size_t size, size_t alignment) {}
static void* allocNonZeroedAlignedImpl(
    void* ctx, size_t size, size_t alignment
) {}

/// given an arena, return an allocator
Allocator arenaToAllocator(Arena* arena) {}
