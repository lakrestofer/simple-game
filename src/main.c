// #include "flecs.h"
#include "window.h"
#include "std/preamble.h"

#define PIXEL_W 640
#define PIXEL_H 340

typedef struct Pos {
    int x;
    int y;
} Pos;

typedef struct Player {
    Pos pos;
} Player;

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
    return 0;
}
