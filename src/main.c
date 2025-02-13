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
#include "sokol_log.h"
#include "glfw_glue.h"
#define NK_IMPLEMENTATION
#include "nuklear.h"
#define SOKOL_NUKLEAR_NO_SOKOL_APP // do not depend on sokol_app.h
#include "sokol_nuklear.h"
#include "macro_utils.h"

#define NK_NEW_FRAME(ctx) ctx = snk_new_frame()
#define NK_END_FRAME() snk_render(glfw_width(), glfw_height())

/// struct containing event information, to be digested by nuklear
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
} _glfw_nk_state_t;

static _glfw_nk_state_t _glfw_nuklear;

static void cursor_position_callback(GLFWwindow* w, double x, double y) {
  int ix = (int)x;
  int iy = (int)y;
  if (_glfw_nuklear.mouse_pos[0] != ix || _glfw_nuklear.mouse_pos[1] != iy) {
    _glfw_nuklear.mouse_did_move = true;
  }
  _glfw_nuklear.mouse_pos[0] = ix;
  _glfw_nuklear.mouse_pos[1] = iy;
}
static void
mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
  if (action == GLFW_PRESS) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
      _glfw_nuklear.btn_down[NK_BUTTON_RIGHT] = true;
    if (button == GLFW_MOUSE_BUTTON_LEFT)
      _glfw_nuklear.btn_down[NK_BUTTON_LEFT] = true;
  }
  if (action == GLFW_RELEASE) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
      _glfw_nuklear.btn_up[NK_BUTTON_RIGHT] = true;
    if (button == GLFW_MOUSE_BUTTON_LEFT)
      _glfw_nuklear.btn_up[NK_BUTTON_LEFT] = true;
  }
}

static void nuklear_handle_glfw_event(struct nk_context* ctx) {
  defer(nk_input_begin(ctx), nk_input_end(ctx)) {
    if (_glfw_nuklear.mouse_did_move) {
      nk_input_motion(
          ctx, _glfw_nuklear.mouse_pos[0], _glfw_nuklear.mouse_pos[1]
      );
      _glfw_nuklear.mouse_did_move = false;
    }
    for (int i = 0; i < NK_BUTTON_MAX; i++) {
      if (_glfw_nuklear.btn_down[i]) {
        _glfw_nuklear.btn_down[i] = false;
        nk_input_button(
            ctx,
            (enum nk_buttons)i,
            _glfw_nuklear.mouse_pos[0],
            _glfw_nuklear.mouse_pos[1],
            1
        );
      } else if (_glfw_nuklear.btn_up[i]) {
        _glfw_nuklear.btn_up[i] = false;
        nk_input_button(
            ctx,
            (enum nk_buttons)i,
            _glfw_nuklear.mouse_pos[0],
            _glfw_nuklear.mouse_pos[1],
            0
        );
      }
    }
  }
}

int main(void) {

  // create window and GL context via GLFW
  glfw_init(&(glfw_desc_t){
      .title           = "simple-game",
      .width           = 640,
      .height          = 480,
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
  glfwSetCursorPosCallback(glfw_window(), cursor_position_callback);
  glfwSetMouseButtonCallback(glfw_window(), mouse_button_callback);

  // a vertex buffer
  const float vertices[] = {// positions            // colors
                            0.0f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
                            0.5f,  -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
                            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f
  };
  sg_buffer vbuf =
      sg_make_buffer(&(sg_buffer_desc){.data = SG_RANGE(vertices)});

  // a shader
  sg_shader shd = sg_make_shader(&(sg_shader_desc
  ){.vertex_func.source   = "#version 410\n"
                            "layout(location=0) in vec4 position;\n"
                            "layout(location=1) in vec4 color0;\n"
                            "out vec4 color;\n"
                            "void main() {\n"
                            "  gl_Position = position;\n"
                            "  color = color0;\n"
                            "}\n",
    .fragment_func.source = "#version 410\n"
                            "in vec4 color;\n"
                            "out vec4 frag_color;\n"
                            "void main() {\n"
                            "  frag_color = color;\n"
                            "}\n"});

  // a pipeline state object (default render states are fine for triangle)
  sg_pipeline pip = sg_make_pipeline(&(sg_pipeline_desc
  ){.shader = shd,
    .layout = {
        .attrs =
            {[0].format = SG_VERTEXFORMAT_FLOAT3,
             [1].format = SG_VERTEXFORMAT_FLOAT4}
    }});

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
    struct nk_context* ctx = NULL;
    defer(NK_NEW_FRAME(ctx), NK_END_FRAME()) {
      nuklear_handle_glfw_event(ctx);
      enum { EASY, HARD };
      static int op      = EASY;
      static float value = 0.6f;
      if (nk_begin(
              ctx,
              "Show",
              nk_rect(50, 50, 220, 220),
              NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_CLOSABLE
          )) {
        /* fixed widget pixel width */
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button")) { /* event handling */
        }

        /* fixed widget window ratio width */
        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;

        /* custom widget pixel width */
        nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
        {
          nk_layout_row_push(ctx, 50);
          nk_label(ctx, "Volume:", NK_TEXT_LEFT);
          nk_layout_row_push(ctx, 110);
          nk_slider_float(ctx, 0, &value, 1.0f, 0.1f);
        }
        nk_layout_row_end(ctx);
      }
      nk_end(ctx);
    }

    sg_end_pass();
    sg_commit();
    glfwSwapBuffers(glfw_window());
    glfwPollEvents();
  }

  // cleanup
  snk_shutdown();
  sg_shutdown();
  glfwTerminate();
  return 0;
}
