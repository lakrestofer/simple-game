#ifndef LINKED_LIST_IMPL
    #error "This is an internal header. Do not include it."
#else

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

    // naming macros
    #define LINKED_LIST_FUNC_IDENT(name) \
        MCONCAT(LINKED_LIST_FUNCTION_PREFIX, name)

    // name of linked list struct type
    #define LinkedListType MCONCAT(LINKED_LIST_VALUE_TYPE, LinkedList)

#endif  // LINKED_LIST_IMPL
