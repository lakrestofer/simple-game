#ifndef INIT_HEADER_DEFINED
#define INIT_HEADER_DEFINED

#include "glad/gl.h"
#include <GLFW/glfw3.h>


GLFWwindow* initAndCreateWindow(int w, int h, char* title);

void registerGlfwCallbacks(GLFWwindow* w, GLFWframebuffersizefun fsfun, GLFWcursorposfun cbfun);


#endif
