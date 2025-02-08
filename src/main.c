// system dependencies
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <cglm/cglm.h>
#include <cglm/mat4.h>
#include <stdbool.h>
#include <sys/stat.h>
// local dependencies
#include "init.h"

int H    = 480;
int W    = 640;
char* WT = "Hello World";
vec3 UP  = {0, 1, 0};

float cube_vertices[] = {
    -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
    1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,

    -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f,
    -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

    1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,

    -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f,
    1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f
};

// aliases
#define shaderVar glGetUniformLocation

// === callbacks ===

void onResizeScreen(GLFWwindow* _, int w, int h) {
  glViewport(0, 0, w, h);
  W = w;
  H = h;
}

// === application code ===

// === shader paths ===
// vertex shaders

// === ASSETS ===
#define closeWindow() glfwSetWindowShouldClose(w, true);
#define K(key) GLFW_KEY_##key
#define keyPressed(key) ((glfwGetKey(w, K(key))) == (GLFW_PRESS))
#define keyReleased(key) ((glfwGetKey(w, K(key))) == (GLFW_RELEASE))
void handleInput(GLFWwindow* w) {
  if (keyPressed(ESCAPE)) closeWindow();
}

int main(void) {
  // === Init glfw and gl context ===
  GLFWwindow* w = initAndCreateWindow(W, H, WT);
  if (!w) {
    glfwTerminate();
    return 1;
  };

  // === register callbacks ==
  registerGlfwCallbacks(w, onResizeScreen, NULL);

  // === load, compile and link shaders ==

  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

  // === Application loop ==
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  while (!glfwWindowShouldClose(w)) {
    // === update ===
    handleInput(w);
    // === draw ===

    // glfw: swap buffers
    glfwSwapBuffers(w); // swap buffer
    glfwPollEvents();   // poll for more events
  }

  // === Cleanup ===
  glfwTerminate();
  return 0;
}
