#ifndef LINKED_LIST_IMPL
    #error "This is an internal header. Do not include it."
#endif

#include "std/macros/macro_utils.h"

// =======================================================================
// IDENTIFIER MACROS
//
// this header file will take the options defined by the user and generate
// identifiers that is then used in the declarations.t.h and definitions.t.h
// file
//
// these macros are then undefined in the unmacro.t.h file (such that
// repeated) inclusion of these templates can be performed
// =======================================================================

// intList -> intListAdd
#define LINKED_LIST_FUNC_IDENT(name) MCONCAT(LINKED_LIST_FUNCTION_PREFIX, name)
// Int -> IntLinkedList
// Int -> IntNode
#define LINKED_LIST_TYPE_IDENT(name) MCONCAT(LINKED_LIST_VALUE_NAME, name)

// name of linked list struct type
#define LinkedList LINKED_LIST_TYPE_IDENT(LinkedList)
#define Node LINKED_LIST_TYPE_IDENT(Node)
#define NodeValue LINKED_LIST_VALUE_TYPE

#undef LINKED_LIST_FUNC_IDENT
