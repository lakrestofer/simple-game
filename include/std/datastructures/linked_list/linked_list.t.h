// =======================================================================
// # Required macro definitions check
//
// we here check that all the required macros are defined
// if not, there will be no linked list for you!
//
// ## description of the macros
//
// - LINKED_LIST_FUNCTION_PREFIX
//   - the prefix of every generated function
// - LINKED_LIST_VALUE_TYPE
//   - the type of the value contained in every list node
//   - must contain a next and previous field
//   - `int`
// - LINKED_LIST_VALUE_NAME
//   - the name of the type, as it should be prefixed to any generated types
// =======================================================================

#ifndef LINKED_LIST_FUNCTION_PREFIX
    #error "LINKED_LIST_FUNCTION_PREFIX" is not defined."
#endif
#ifndef LINKED_LIST_VALUE_TYPE
    #error "LINKED_LIST_VALUE_TYPE" is not defined."
#endif
#ifndef LINKED_LIST_VALUE_NAME
    #error "LINKED_LIST_VALUE_NAME" is not defined."
#endif

// =======================================================================
// # Template expansion
//
// here we include the templates that will generate the declarations
// and definitions of your linked list
//
// ## Description of headers
//
// - macros.t.h - will define identifier macros
// - declarations.t.h - using the identifiers, generate the declarations
// - definitions.t.h - using the identifiers, generate the definitions
// - unmacros.t.h - undef the identifier macros
// =======================================================================

#define LINKED_LIST_IMPL

#include "std/datastructures/linked_list/impl/macros.t.h"
#include "std/datastructures/linked_list/impl/declarations.t.h"
#include "std/datastructures/linked_list/impl/definitions.t.h"
#include "std/datastructures/linked_list/impl/unmacros.t.h"

#undef LINKED_LIST_IMPL
