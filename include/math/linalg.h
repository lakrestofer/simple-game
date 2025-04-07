
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
    int x, y, z;
  };
  struct {
    int width, height, depth;
  };
  int elements[3];
} IVec3;

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
  struct {
    float r, g, b;
  };
  float elements[3];
} FVec3;
typedef FVec3 FColor;
