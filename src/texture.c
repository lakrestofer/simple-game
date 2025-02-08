#include "texture.h"
#include "external/stb_image.h"
#include <stdbool.h>

ImageData* loadTextureData(const char** paths, int n_faces) {
  ImageData* textures = calloc(n_faces, sizeof(ImageData));
  for (int i = 0; i < n_faces; i++) {
    const char* path = paths[i];
    int iw, ih, nbrChnls;
    unsigned char* data = stbi_load(paths[i], &iw, &ih, &nbrChnls, 3);
    if (!data) {
      printf("could not cube map path: %s\n", path);
      return NULL;
    };
    textures[i].format = nbrChnls;
    textures[i].h      = ih;
    textures[i].w      = iw;
    textures[i].data   = data;
  }
  return textures;
}
