#pragma once

#include <string>
#include <utility>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Display {
  static int instances;
  static bool glew_was_initialized;

  GLFWwindow *m_window_ptr;
  int m_width, m_height, m_frame_width, m_frame_height;
  bool m_should_close = false;
  bool m_context_was_made_current = false;

public:
  Display(const char *title, int width, int height);

  ~Display();
  Display(const Display &) = delete;
  Display &operator=(const Display &) = delete;

  void swap_buffers() const { glfwSwapBuffers(m_window_ptr); };
  void make_context_current();

  [[nodiscard]] bool should_close() const { return m_should_close; };
  [[nodiscard]] int width() const { return m_width; };
  [[nodiscard]] int height() const { return m_height; };
  [[nodiscard]] int frame_width() const { return m_frame_width; };
  [[nodiscard]] int frame_height() const { return m_height; };
};
