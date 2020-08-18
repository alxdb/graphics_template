#pragma once

#include <GL/glew.h>

namespace oogl {

class Object {
protected:
  GLuint m_id;
  ~Object() = default;

public:
  Object(const Object &obj) = delete;
  Object &operator=(Object other) = delete;

  Object(Object &&obj) {
    m_id = obj.m_id;
    obj.m_id = 0;
  }

  Object() : m_id(0){};
  [[nodiscard]] GLuint id() const { return m_id; }
};

} // namespace oogl

#include "Buffer.hpp"
#include "Program.hpp"
#include "VertexArray.hpp"
