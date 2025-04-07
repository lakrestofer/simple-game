#ifndef WINDOW_H_DEFINED
#define WINDOW_H_DEFINED

#include <GLFW/glfw3.h>

/// retrieve the glfw window object
GLFWwindow* getWindow();
/// get the window height
int getWindowHeight();
/// get the window width
int getWindowWidth();

/// create a window
void createWindow(char* title);

/// destroy the application window
void destroyWindow();

#endif  // WINDOW_H_DEFINED
