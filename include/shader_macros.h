#ifndef SHADER_MACRO_UTILS_HEADER_DEFINED
#define SHADER_MACRO_UTILS_HEADER_DEFINED

#define GLSL(src) "#version 410 core\n" #src

#define SG_SHADER_DESC(VERT_SRC, FRAG_SRC)                                     \
  (sg_shader_desc) {                                                           \
    .vertex_func.source = VERT_SRC, .fragment_func.source = FRAG_SRC           \
  }

#endif // SHADER_MACRO_UTILS_HEADER_DEFINED
