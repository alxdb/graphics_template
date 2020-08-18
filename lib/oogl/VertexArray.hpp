#pragma once

#include "oogl.hpp"

namespace oogl {
struct VertexAttributeFormat {
  GLint size = 4;
  GLenum type = GL_FLOAT;
  GLboolean normalized = GL_FALSE;
  GLuint relativeoffset = 0;
};

class VertexArray : public Object {
  static GLuint current_binding;

public:
  VertexArray() { glGenVertexArrays(1, &m_id); }
  ~VertexArray() { glDeleteVertexArrays(1, &m_id); }

  void bind() const;

  void set_attrib_format(GLuint attrib_index, VertexAttributeFormat format) const;
  void set_buffer_binding(GLuint binding_index,
                          const Buffer &buffer,
                          GLintptr offset,
                          GLintptr stride) const;
  void set_attrib_binding(GLuint attrib_index, GLuint binding_index) const;
  void enable_attrib(GLuint attrib_index) const;
};

}; // namespace oogl
