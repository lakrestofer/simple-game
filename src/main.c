#include "flecs.h"
#include "macro_utils.h"
#include "window.h"
#include <GL/gl.h>

int main(void) {
  defer(createWindow("some title"), destroyWindow()) {
    while (!glfwWindowShouldClose(getWindow())) {
      /* Render here */
      glClear(GL_COLOR_BUFFER_BIT);

      /* Swap front and back buffers */
      glfwSwapBuffers(getWindow());

      /* Poll for and process events */
      glfwPollEvents();
    }
  }
}
