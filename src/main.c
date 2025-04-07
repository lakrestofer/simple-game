//------------------------------------------------------------------------------
//  triangle-glfw.c
//  Vertex buffer, simple shader, pipeline state object.
//------------------------------------------------------------------------------
#define SOKOL_IMPL
#define SOKOL_GLCORE
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_INCLUDE_STANDARD_VARARGS
#include "sokol_gfx.h"
#include "glfw_glue.h"
#include "sokol_log.h"
#define NK_IMPLEMENTATION
#include "nuklear.h"
#define SOKOL_NUKLEAR_NO_SOKOL_APP  // do not depend on sokol_app.h
#include "flecs.h"
#include "macro_utils.h"
#include "sokol_nuklear.h"

// util macros
#define NK_NEW_FRAME(ctx) ctx = snk_new_frame()
#define NK_END_FRAME() snk_render(glfw_width(), glfw_height())
#define UNUSED(expr) (void)expr

// constants

// util typedefs
typedef int button_t;
typedef int action_t;
typedef int mod_t;

typedef union {
  struct {
    int x, y;
  };
  struct {
    int u, v;
  };
  struct {
    int left, right;
  };
  struct {
    int width, height;
  };
  int elements[2];
} IVec2;

typedef union {
  struct {
    float x, y;
  };
  struct {
    float u, v;
  };
  struct {
    float left, right;
  };
  struct {
    float width, height;
  };
  float elements[2];
} FVec2;

typedef union {
  struct {
    float x, y, z;
  };
  float elements[3];
} FVec3;
typedef union {
  struct {
    float r, g, b;
  };
  float elements[3];
} FColor;
typedef uint64_t Index;
// struct containing event information, to be digested by nuklear
typedef struct {
  int mouse_pos[2];
  float mouse_scroll[2];
  bool mouse_did_move;
  bool mouse_did_scroll;
  bool btn_down[NK_BUTTON_MAX];
  bool btn_up[NK_BUTTON_MAX];
  char char_buffer[NK_INPUT_MAX];
  bool keys_down[NK_KEY_MAX];
  bool keys_up[NK_KEY_MAX];
} glfw_nk_state_t;

// glfw input event callbacks
static void cursorPosCb(GLFWwindow *w, double x, double y);
static void mouseBtnCb(GLFWwindow *w, button_t b, action_t a, mod_t m);

/// given the global state in _glfw_nuklear, pass it to nuklear and reset.
static void nkHandleGlfwEvent(struct nk_context *ctx);

/// initialize global state of glfw, sokol and nuklear.
static void simpleGameInitGfx(void);
/// clean global state of glfw, sokol and nuklear.
static void simpleGameCleanGfx(void);

// global state!
static glfw_nk_state_t glfw_nuklear;

// clang-format off
const float vertices[] = {
      // positions            // colors
       0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
       0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
  };
// clang-format on

ecs_world_t *world = NULL;

const char *TRNGL_VERT_SHAD_SRC =
  "#version 410\n"
  "layout(location=0) in vec4 position;\n"
  "layout(location=1) in vec4 color0;\n"
  "out vec4 color;\n"
  "void main() {\n"
  "  gl_Position = position;\n"
  "  color = color0;\n"
  "}\n";

const char *TRNGL_FRAG_SHAD_SRC =
  "#version 410\n"
  "in vec4 color;\n"
  "out vec4 frag_color;\n"
  "void main() {\n"
  "  frag_color = color;\n"
  "}\n";

int main(void) {
  simpleGameInitGfx();  // initalize glfw, sokol and nuklear
  glfwSetInputMode(glfw_window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  world = ecs_init();

  ECS_COMPONENT(world, FVec2);
  ecs_entity_t e = ecs_entity(world, {.name = "Triangle"});

  // create window and GL context via GLFW
  sg_buffer vbuf = sg_make_buffer(&(sg_buffer_desc){
    .data = SG_RANGE(vertices),
  });

  // a shader
  sg_shader_desc shd_desc = {
    .vertex_func.source = TRNGL_VERT_SHAD_SRC,
    .fragment_func.source = TRNGL_FRAG_SHAD_SRC,
  };
  sg_shader shd = sg_make_shader(&shd_desc);

  // a pipeline state object (default render states are fine for triangle)
  sg_pipeline_desc pip_desc = {
    .shader = shd,
    .layout =
      {
        .attrs =
          {
            [0].format = SG_VERTEXFORMAT_FLOAT3,
            [1].format = SG_VERTEXFORMAT_FLOAT4,
          },
      },
  };
  sg_pipeline pip = sg_make_pipeline(&pip_desc);

  // resource bindings
  sg_bindings bind = {.vertex_buffers[0] = vbuf};

  // draw loop
  while (!glfwWindowShouldClose(glfw_window())) {
    sg_begin_pass(&(sg_pass){.swapchain = glfw_swapchain()});
    // shader
    sg_apply_pipeline(pip);
    sg_apply_bindings(&bind);
    sg_draw(0, 3, 1);

    // pass events to nuklear
    // draw Nuklear ui
    struct nk_context *ctx = NULL;
    defer(NK_NEW_FRAME(ctx), NK_END_FRAME()) {
      nkHandleGlfwEvent(ctx);
      if (nk_begin(ctx,
                   "Show",
                   nk_rect(50, 50, 220, 220),
                   NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE)) {
        /* fixed widget pixel width */
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button")) { /* event handling */
        }
      }
      nk_end(ctx);
    }

    sg_end_pass();
    sg_commit();
    glfwSwapBuffers(glfw_window());
    glfwPollEvents();
  }

  // cleanup
  ecs_fini(world);
  simpleGameCleanGfx();
  return 0;
}

static void cursorPosCb(GLFWwindow *w, double x, double y) {
  UNUSED(w);
  int ix = (int)x;
  int iy = (int)y;
  if (glfw_nuklear.mouse_pos[0] != ix || glfw_nuklear.mouse_pos[1] != iy) {
    glfw_nuklear.mouse_did_move = true;
  }
  glfw_nuklear.mouse_pos[0] = ix;
  glfw_nuklear.mouse_pos[1] = iy;
}

static void mouseBtnCb(GLFWwindow *win, int button, int action, int mod) {
  UNUSED(win);
  UNUSED(mod);
  if (action == GLFW_PRESS) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
      glfw_nuklear.btn_down[NK_BUTTON_RIGHT] = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      glfw_nuklear.btn_down[NK_BUTTON_LEFT] = true;
    }
  }
  if (action == GLFW_RELEASE) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
      glfw_nuklear.btn_up[NK_BUTTON_RIGHT] = true;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      glfw_nuklear.btn_up[NK_BUTTON_LEFT] = true;
    }
  }
}

static void nkHandleGlfwEvent(struct nk_context *ctx) {
  defer(nk_input_begin(ctx), nk_input_end(ctx)) {
    if (glfw_nuklear.mouse_did_move) {
      nk_input_motion(
        ctx, glfw_nuklear.mouse_pos[0], glfw_nuklear.mouse_pos[1]);
      glfw_nuklear.mouse_did_move = false;
    }
    for (int i = 0; i < NK_BUTTON_MAX; i++) {
      if (glfw_nuklear.btn_down[i]) {
        glfw_nuklear.btn_down[i] = false;
        nk_input_button(ctx,
                        (enum nk_buttons)i,
                        glfw_nuklear.mouse_pos[0],
                        glfw_nuklear.mouse_pos[1],
                        1);
      } else if (glfw_nuklear.btn_up[i]) {
        glfw_nuklear.btn_up[i] = false;
        nk_input_button(ctx,
                        (enum nk_buttons)i,
                        glfw_nuklear.mouse_pos[0],
                        glfw_nuklear.mouse_pos[1],
                        0);
      }
    }
  }
}

/// initialize global state of glfw, sokol and nuklear.
static void simpleGameInitGfx(void) {
  glfw_init(&(glfw_desc_t){
    .title = "simple-game",
    .width = 640,
    .height = 480,
    .no_depth_buffer = true,
  });
  // setup sokol_gfx
  sg_setup(&(sg_desc){
    .environment = glfw_environment(),
    .logger.func = slog_func,
  });
  // setup sokol_nuklear
  snk_desc_t setup_nuklear_desc = {0};
  snk_setup(&setup_nuklear_desc);
  // setup mouse callback
  glfwSetCursorPosCallback(glfw_window(), cursorPosCb);
  glfwSetMouseButtonCallback(glfw_window(), mouseBtnCb);
}

static void simpleGameCleanGfx(void) {
  snk_shutdown();
  sg_shutdown();
  glfwTerminate();
}
