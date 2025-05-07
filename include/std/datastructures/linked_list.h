#pragma once

#include <stdbool.h>
#include "std/macros/container_of.h"

// ============================================================================
// Type definitions
// ============================================================================

typedef struct List List;

struct List {
    List* prev;
    List* next;
};

// ============================================================================
// Function definitions
// ============================================================================

// ----------------------------------------------------------------------------
// public
// ----------------------------------------------------------------------------

static inline void listAppend(List* list, List* new);
static inline void listPrepend(List* list, List* new);

static inline void listDelete(List* list);

static inline void listReplace(List* old, List* new);
static inline void listSwap(List* l1, List* l2);

static inline bool listIsFirst(List* list, List* head);
static inline bool listIsLast(List* list, List* head);
static inline bool listIsHead(List* list, List* head);
static inline bool listIsEmpty(List* list);

#define listEntry(ptr, type, member) container_of(ptr, type, member)

// NOLINTBEGIN(bugprone-macro-parentheses)
#define listForEach(pos, head) \
    for (pos = (head)->next; !listIsHead(pos, (head)); pos = pos->next)
// NOLINTEND(bugprone-macro-parentheses)
// ----------------------------------------------------------------------------
// private
// ----------------------------------------------------------------------------

/// PRIVATE do not use directly. Add new between prev and next
static inline void listAddBetween_(List* new, List* prev, List* next);
static inline void listDel_(List* prev, List* next);

// ============================================================================
// Function implementations
// ============================================================================

// ----------------------------------------------------------------------------
// public
// ----------------------------------------------------------------------------

static inline void listAppend(List* list, List* new) {
    // add new after list
    listAddBetween_(new, list, list->next);
}
static inline void listPrepend(List* list, List* new) {
    // add new before list
    listAddBetween_(new, list->prev, list);
}

static inline void listDelete(List* list) { listDel_(list->prev, list->next); }
static inline void listReplace(List* old, List* new) {
    new->next = old->next;
    new->next->prev = new;
    new->prev = old->prev;
    new->prev->next = new;
}
static inline void listSwap(List* entry1, List* entry2) {
    List* position = entry2->prev;
    listDelete(entry2);
    listReplace(entry1, entry2);
    if (position == entry1) position = entry2;
    listAppend(position, entry1);
}

static inline bool listIsFirst(List* list, List* head) {
    return list->prev == head;
}
static inline bool listIsLast(List* list, List* head) {
    return list->next == head;
}
static inline bool listIsHead(List* list, List* head) { return list == head; }
static inline bool listIsEmpty(List* list) { return list->next == list->prev; }

// ----------------------------------------------------------------------------
// private
// ----------------------------------------------------------------------------

// private helpers implementations
static inline void listAddBetween_(List* new, List* prev, List* next) {
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}
static inline void listDel_(List* prev, List* next) {
    next->prev = prev;
    prev->next = next;
}
