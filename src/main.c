#include "flecs.h"

typedef union {
  struct {
    int x, y;
  };
  struct {
    int u, v;
  };
  struct {
    int left, right;
  };
  struct {
    int width, height;
  };
  int elements[2];
} IVec2;

typedef union {
  struct {
    float x, y;
  };
  struct {
    float u, v;
  };
  struct {
    float left, right;
  };
  struct {
    float width, height;
  };
  float elements[2];
} FVec2;

typedef union {
  struct {
    float x, y, z;
  };
  float elements[3];
} FVec3;
typedef union {
  struct {
    float r, g, b;
  };
  float elements[3];
} FColor;

const char *TRNGL_VERT_SHAD_SRC =
  "#version 410\n"
  "layout(location=0) in vec4 position;\n"
  "layout(location=1) in vec4 color0;\n"
  "out vec4 color;\n"
  "void main() {\n"
  "  gl_Position = position;\n"
  "  color = color0;\n"
  "}\n";

const char *TRNGL_FRAG_SHAD_SRC =
  "#version 410\n"
  "in vec4 color;\n"
  "out vec4 frag_color;\n"
  "void main() {\n"
  "  frag_color = color;\n"
  "}\n";

int main(void) { printf("hello world\n"); }
