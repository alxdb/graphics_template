#include "VertexArray.hpp"

namespace oogl {

GLuint VertexArray::current_binding = 0;

void VertexArray::bind() const {
  if (current_binding != m_id) {
    glBindVertexArray(m_id);
    current_binding = m_id;
  }
}

void VertexArray::set_attrib_format(GLuint attrib_index,
                                    VertexAttributeFormat format) const {
  bind();
  glVertexAttribFormat(attrib_index,
                       format.size,
                       format.type,
                       format.normalized,
                       format.relativeoffset);
}

void VertexArray::set_buffer_binding(GLuint binding_index,
                                     const Buffer &buffer,
                                     GLintptr offset,
                                     GLintptr stride) const {
  bind();
  glBindVertexBuffer(binding_index, buffer.id(), offset, stride);
}

void VertexArray::set_attrib_binding(GLuint attrib_index, GLuint binding_index) const {
  bind();
  glVertexAttribBinding(attrib_index, binding_index);
}

void VertexArray::enable_attrib(GLuint attrib_index) const {
  bind();
  glEnableVertexAttribArray(attrib_index);
}

} // namespace oogl
