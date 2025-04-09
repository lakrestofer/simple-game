#define LINKED_LIST_IMPL

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
// =======================================================================

// toggle whether to check for the required macros or not
#define CHECK_MACROS_DEFINED

#ifdef CHECK_MACROS_DEFINED
    #ifndef LINKED_LIST_FUNCTION_PREFIX
        #error "LINKED_LIST_FUNCTION_PREFIX" is not defined."
    #endif
    #ifndef LINKED_LIST_VALUE_TYPE
        #error "LINKED_LIST_VALUE_TYPE" is not defined."
    #endif
#endif

// toggle whether to check for the fields
#define CHECK_TYPES_VALID

#if defined(CHECK_TYPES_VALID) && defined(LINKED_LIST_VALUE_TYPE)
    #include "std/macros/types/assert_has_field.h"

STATIC_ASSERT_HAS_FIELD(LINKED_LIST_VALUE_TYPE, next);
STATIC_ASSERT_HAS_FIELD(LINKED_LIST_VALUE_TYPE, previous);

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

#include "std/datastructures/linked_list/impl/macros.t.h"
#include "std/datastructures/linked_list/impl/declarations.t.h"
#include "std/datastructures/linked_list/impl/definitions.t.h"
#include "std/datastructures/linked_list/impl/unmacros.t.h"

#undef LINKED_LIST_IMPL
