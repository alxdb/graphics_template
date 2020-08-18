#include <filesystem>

#include <Display.hpp>
#include <oogl/oogl.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace fs = std::filesystem;

class App {
  Display display;

public:
  App() : display("graphics_template_project", 1920, 1080) {
    display.make_context_current();
    spdlog::set_level(spdlog::level::debug);
  };

  void run() {
    oogl::Program program({
        {GL_VERTEX_SHADER, fs::path("resources/shader.vert")},
        {GL_FRAGMENT_SHADER, fs::path("resources/shader.frag")},
    });

    std::vector<float> triangle_points{-0.5, -0.5, 0.5, -0.5, 0.0, 0.5};
    oogl::Buffer triangle_vbo(triangle_points);

    oogl::VertexArray vao;
    vao.set_buffer_binding(0, triangle_vbo, 0, 2 * sizeof(float));
    vao.enable_attrib(0);
    vao.set_attrib_format(0, {2});
    vao.set_attrib_binding(0, 0);

    program.use();

    while (!display.should_close()) {
      glfwPollEvents();
      glClear(GL_COLOR_BUFFER_BIT);
      glDrawArrays(GL_TRIANGLES, 0, 3);
      display.swap_buffers();
    }
  }
};

int main() {
  App app;
  app.run();
}
