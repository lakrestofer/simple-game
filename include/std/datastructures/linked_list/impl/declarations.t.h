#ifndef LINKED_LIST_IMPL
    #error "This is an internal header. Do not include it."
#endif

#include <stddef.h>

typedef struct Node Node;

struct Node {
    Node* next;
    Node* previous;
    NodeValue value;
};

typedef struct LinkedList {
    Node* head;
    Node* tail;
    size_t count;
} LinkedList;
