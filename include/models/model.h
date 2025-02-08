#ifndef MODEL_HEADER_DEFINED
#define MODEL_HEADER_DEFINED

#include "glad/gl.h"
#include "texture.h"

typedef enum {
  VERTEX,
  NORMAL,
  TANGENT,
  TEXCOORD,
  BINORMAL,
  N_BUFFER_TYPES
} BufferType;

// the number of floats in each buffer type
static const char COMPONENT_SIZE[N_BUFFER_TYPES] = {3, 3, 4, 2, 3};

typedef struct {
  int n_vertices;
  int n_triangles;
  float* vertices;
  float* normals;
  float* tangents;
  float* tex_coords;
  float* binormals;
  unsigned int* indices;
} Mesh;



#ifndef MODEL_CONSTANTS_DEFINED
#define MODEL_CONSTANTS_DEFINED
static const int FORMAT_TO_GL_FORMAT[N_IMAGE_FORMATS] = { GL_RED, GL_RG, GL_RGB, GL_RGBA };
#endif

typedef struct {
  ImageData textures[N_TEXTURE_TYPES];
} Material;


typedef struct {
  int n_meshes;
  int n_materials;
  Mesh* meshes;
  Material* materials;
} Model;


typedef enum {
  SUCCESS,
  ERROR,
} LoadModelRes;


LoadModelRes loadModelFromGltfFile(const char* path, Model* model);

void freeMesh(Mesh* mesh);
void freeModel(Model* model);

#endif
