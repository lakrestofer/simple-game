#ifndef MACRO_UTILS_H_DEFINED
#define MACRO_UTILS_H_DEFINED

#define UNUSED(expr) (void)expr

#define GLSL(src) "#version 410 core\n" #src

#define macro_var(name) name##__LINE__

#define defer(start, end)                                \
  for (int macro_var(_i_) = (start, 0); !macro_var(_i_); \
       (macro_var(_i_) = 1), end)

#endif  // MACRO_UTILS_H_DEFINED
