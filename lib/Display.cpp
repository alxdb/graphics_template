#include "Display.hpp"

#include <sstream>
#include <stdexcept>

#include <spdlog/spdlog.h>

int Display::instances = 0;

Display::Display(const char *title, int width, int height)
    : m_width(width), m_height(height), m_frame_width(width), m_frame_height(height) {
  if (instances++ == 0) {
    auto glfw_error_callback = [](int error, const char *description) {
      spdlog::error("GLFW Error ({}): {}", error, description);
    };
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
      throw std::runtime_error("GLFW init failed");
    }
    spdlog::info("GLFW Initialized");
  }

  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

  m_window_ptr = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if (m_window_ptr == nullptr) {
    throw std::runtime_error("Window Creation Failed");
  }
  glfwSetWindowUserPointer(m_window_ptr, this);

  glfwSetWindowSizeCallback(m_window_ptr, [](GLFWwindow *window, int width, int height) {
    auto self = (Display *)glfwGetWindowUserPointer(window);
    self->m_width = width;
    self->m_height = height;
  });

  auto framebuffer_size_callback = [](GLFWwindow *window, int width, int height) {
    auto self = (Display *)glfwGetWindowUserPointer(window);
    self->m_frame_width = width;
    self->m_frame_height = height;
    if (glfwGetCurrentContext() == window) {
      glViewport(0, 0, width, height);
    }
  };
  glfwSetFramebufferSizeCallback(m_window_ptr, framebuffer_size_callback);

  glfwSetWindowCloseCallback(m_window_ptr, [](GLFWwindow *window) {
    auto self = (Display *)glfwGetWindowUserPointer(window);
    self->m_should_close = true;
  });

  spdlog::info("Display Constructed");
}

bool Display::glew_was_initialized = false;

void Display::make_context_current() {
  if (glfwGetCurrentContext() != m_window_ptr) {
    glfwMakeContextCurrent(m_window_ptr);
    if (!glew_was_initialized) {
      GLenum error = glewInit();
      if (error != GLEW_OK) {
        std::stringstream err_s;
        err_s << "GLEW Failed to initialize: ";
        err_s << glewGetErrorString(error);
        throw std::runtime_error(err_s.str());
      }
      glew_was_initialized = true;
      spdlog::info("GLEW Initialized");
    }

    if (!m_context_was_made_current) {
      auto gl_debug_callback = [](GLenum,
                                  GLenum,
                                  GLuint,
                                  GLenum severity,
                                  GLsizei,
                                  const GLchar *message,
                                  const void *) {
        std::stringstream err_s;
        err_s << "OpenGL: ";
        err_s << message;
        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
          throw std::runtime_error(err_s.str());
        case GL_DEBUG_SEVERITY_MEDIUM:
          spdlog::warn(err_s.str());
        case GL_DEBUG_SEVERITY_LOW:
          spdlog::info(err_s.str());
        default:
          spdlog::debug(err_s.str());
        }
      };

      glEnable(GL_DEBUG_OUTPUT);
      glDebugMessageCallback(gl_debug_callback, nullptr);
      spdlog::info("OpenGL Debug Callback Set");
      m_context_was_made_current = true;
    }
  }
}

Display::~Display() {
  if (m_window_ptr != nullptr) {
    glfwDestroyWindow(m_window_ptr);
    spdlog::info("Display Destructed");

    if (--instances == 0) {
      glfwTerminate();
      spdlog::info("GLFW Terminated");
    }
  }
}
