#ifndef MACRO_UTILS_H_DEFINED
#define MACRO_UTILS_H_DEFINED

// Concatenates arguments.
#define CONCAT(prefix, name) CONCAT_IMPL(prefix, name)
#define CONCAT_IMPL(prefix, name) prefix##name

// Expands macro argument (e.g. allowing it to be used with token pasting or
// stringification.)
#define EXPAND(token) EXPAND_IMPL(token)
#define EXPAND_IMPL(token) token

// Stringifies macro argument.
#define STRINGIFY(token) STRINGIFY_IMPL(token)
#define STRINGIFY_IMPL(token) #token

#endif  // MACRO_UTILS_H_DEFINED
