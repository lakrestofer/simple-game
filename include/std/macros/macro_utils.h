#ifndef MACRO_UTILS_H_DEFINED
#define MACRO_UTILS_H_DEFINED

// =======================================================================
// Macro utils
//
// these macros are for the manipulation and creation of other macros
// =======================================================================

// Concatenates arguments.
#define MCONCAT(prefix, name) MCONCAT_IMPL(prefix, name)
#define MCONCAT_IMPL(prefix, name) prefix##name

// Expands macro argument (e.g. allowing it to be used with token pasting or
// stringification.)
#define MEXPAND(token) MEXPAND_IMPL(token)
#define MEXPAND_IMPL(token) token

// Stringifies macro argument.
#define MSTRINGIFY(token) MSTRINGIFY_IMPL(token)
#define MSTRINGIFY_IMPL(token) #token

// creates a unique (per line) identifier
#define MVAR(name) name##__LINE__

#endif  // MACRO_UTILS_H_DEFINED
