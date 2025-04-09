#ifndef MACRO_CONTROL_FLOW_H_DEFINED
#define MACRO_CONTROL_FLOW_H_DEFINED

// creates a unique (per line) identifier
#define MVAR(name) name##__LINE__

#define defer(start, end) \
    for (int MVAR(_i_) = (start, 0); !MVAR(_i_); (MVAR(_i_) = 1), end)

#endif  // MACRO_CONTROL_FLOW_H_DEFINED
