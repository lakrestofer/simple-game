#include "window.h"
#include "macro_utils.h"

// ===================================================
// private vars begin
// ===================================================
static GLFWwindow* window = NULL;
static int HEIGHT = 400;
static int WIDTH = 600;

// ===================================================
// private function declarations begin
// ===================================================

/// callback for glfwSetFramebufferSizeCallback
static void framebuffer_size_cb(GLFWwindow* win, int w, int h);

// ===================================================
// header implementation begin
// ===================================================
GLFWwindow* getWindow() { return window; }

void createWindow(char* title) {
  glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
  // glfwInitHint(GLFW_WAYLAND_LIBDECOR, GLFW_WAYLAND_PREFER_LIBDECOR);
  if (!glfwInit()) return;

  window = glfwCreateWindow(WIDTH, HEIGHT, title, NULL, NULL);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_cb);

  // init opengl
  glViewport(0, 0, WIDTH, HEIGHT);

  if (!window) {
    glfwTerminate();
    return;
  }
  glfwMakeContextCurrent(window);
}

/// get the window height
int getWindowHeight() { return HEIGHT; }
/// get the window width
int getWindowWidth() { return WIDTH; }

/// destroy the application window
void destroyWindow() { glfwTerminate(); }

// ===================================================
// private function implementation begin
// ===================================================
static void framebuffer_size_cb(GLFWwindow* win, int w, int h) {
  UNUSED(win);
  HEIGHT = h;
  WIDTH = w;
  glViewport(0, 0, w, h);
}
