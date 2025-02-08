#ifndef TEXTUER_HEADER_DEFINED
#define TEXTUER_HEADER_DEFINED
#include "glad/gl.h"

// TODO move out cube map texture from texture type enum
typedef enum {
  T_DIFFUSE,
  T_NORMAL,
  T_ROUGHNESS,
  T_CUBE_MAP,
  N_TEXTURE_TYPES,
} TextureType;

typedef enum {
  GRAY,
  GRAY_ALPHA,
  RED_GREEN_BLUE,
  RED_GEEN_BLUE_ALPHA,
  N_IMAGE_FORMATS
} ImageFormat;

typedef struct {
  int h;
  int w;
  ImageFormat format;
  unsigned char* data;
} ImageData;

typedef struct {
  ImageData image;
} Texture;

typedef enum { PNG, JPG } ImageType;
/// DEPRECATED: loads the image from file and generates gl ints
GLuint loadTexture(const char* fileName, ImageType type);

ImageData* loadTextureData(const char** paths, int n_faces);

#endif
