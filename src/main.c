#include "flecs.h"
#include "window.h"
#include "std/preamble.h"

int main(void) {
    createWindow("some title");
    while (!glfwWindowShouldClose(getWindow())) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(getWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }
    destroyWindow();
}
