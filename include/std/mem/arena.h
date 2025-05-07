#pragma once
#include <stddef.h>
#include <stdint.h>
#include "std/mem/allocator.h"
#include "stdbool.h"

///////////////////////////////////////////////////////////////////////////////
// TYPE DEFINITIONS
///////////////////////////////////////////////////////////////////////////////

typedef struct Arena Arena;
typedef struct ArenaRegion ArenaRegion;

struct Arena {
    ArenaRegion* start;
    ArenaRegion* end;
    Allocator child_allocator;
};

struct ArenaRegion {
    ArenaRegion* next;
    size_t size;
    size_t capacity;
    uint8_t data[];
};

///////////////////////////////////////////////////////////////////////////////
// FUNCTION DEFINITIONS
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// life cycle
// ----------------------------------------------------------------------------

/// Create an arena
Arena arenaNew(Allocator child_allocator);

/// Allocate a region
ArenaRegion* arenaRegionCreate(Allocator* allocator, size_t size);
/// deallocate a region
void arenaRegionDestroy(ArenaRegion* region, Allocator* allocator);

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
void* arenaAlloc(Arena* a, size_t size);
void* arenaAllocNonZeroed(Arena* a, size_t size);
void* arenaAllocAligned(Arena* a, size_t size, size_t alignment);
void* arenaAllocNonZeroedAligned(Arena* a, size_t size, size_t alignment);

/// dealocate memory
void arenaDealloc(Arena* a, void* ptr);

/// resets an arena, freeing all the memory used
void arenaResetFree(Arena* arena);

/// resets an arena, freeing all memory, then allocates a large enough
/// buffer to contain all previous allocations
void arenaResetRetain(Arena* arena);

/// resets an arena, freeing all memory, then allocates a large enough
/// buffer to contain all previous allocations, up to a limit
void arenaResetRetainWithLimit(Arena* arena, size_t limit);

/// given an arena, return an allocator
Allocator arenaToAllocator(Arena* arena);
