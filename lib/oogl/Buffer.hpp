#pragma once

#include <array>
#include <vector>

#include "oogl.hpp"

namespace oogl {

class Buffer : public Object {
  GLenum m_target;
  Buffer(GLenum target) : m_target(target) { glGenBuffers(1, &m_id); };

public:
  ~Buffer() { glDeleteBuffers(1, &m_id); }

  Buffer(void *data, size_t size, GLenum target = GL_ARRAY_BUFFER,
         GLenum usage = GL_STATIC_DRAW)
      : Buffer(target) {
    bind();
    glBufferData(target, size, data, usage);
  }

  template <typename T>
  Buffer(std::vector<T> data, GLenum target = GL_ARRAY_BUFFER,
         GLenum usage = GL_STATIC_DRAW)
      : Buffer(data.data(), sizeof(T) * data.size(), target, usage){};

  template <typename T, size_t N>
  Buffer(std::array<T, N> data, GLenum target = GL_ARRAY_BUFFER,
         GLenum usage = GL_STATIC_DRAW)
      : Buffer(data.data(), sizeof(T) * data.size(), target, usage){};

  void bind() const { glBindBuffer(m_target, m_id); }
};

} // namespace oogl
