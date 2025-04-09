#include "window.h"

// ===================================================
// private vars begin
// ===================================================
static GLFWwindow* win = NULL;
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
GLFWwindow* getWindow() { return win; }

void createWindow(char* title) {
    // glfw init
    glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_WAYLAND);
    if (!glfwInit()) return;

    win = glfwCreateWindow(WIDTH, HEIGHT, title, glfwGetPrimaryMonitor(), NULL);
    glfwSetFramebufferSizeCallback(win, framebuffer_size_cb);
    if (!win) {
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(win);

    // init opengl
    glViewport(0, 0, WIDTH, HEIGHT);
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
static void framebuffer_size_cb(GLFWwindow* window, int w, int h) {
    HEIGHT = h;
    WIDTH = w;
    glViewport(0, 0, w, h);
}
