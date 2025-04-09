#ifndef ARENA_H_DEFINED
#define ARENA_H_DEFINED

#include "allocator.h"
#include "stdbool.h"

typedef struct Arena Arena;

struct Arena {
    Allocator child_allocator;
};

/// Create an arena
Arena arenaNew(Allocator child_allocator);

/// Deinit an arena
void arenaDeinit(Arena* arena);

/// current memory usage of the arena,
/// not including memory used by implementation
size_t arenaMemoryUsage();

/// resets an arena, freeing all the memory used
bool arenaResetFree(Arena* arena);

/// resets an arena, freeing all memory, then allocates a large enough
/// buffer to contain all previous allocations
bool arenaResetRetain(Arena* arena);

/// resets an arena, freeing all memory, then allocates a large enough
/// buffer to contain all previous allocations, up to a limit
bool arenaResetRetainWithLimit(Arena* arena, size_t limit);

/// given an arena, return an allocator
Allocator arenaToAllocator(Arena* arena);

#endif  // ARENA_H_DEFINED
