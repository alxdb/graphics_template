#pragma once

#include "oogl.hpp"

#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace oogl {
class Shader : public Object {
  Shader(GLenum type) { m_id = glCreateShader(type); }

public:
  ~Shader() { glDeleteShader(m_id); }
  Shader(Shader &&shader) : Object(std::move(shader)){};

  Shader(const std::string &source, GLenum type);
  Shader(const std::filesystem::path &source_file, GLenum type);
};

class Program : public Object {
  Program() { m_id = glCreateProgram(); }

public:
  ~Program() { glDeleteProgram(m_id); }

  Program(const std::vector<Shader> &shaders);
  Program(const std::map<GLenum, std::filesystem::path> &shader_sources);

  void use() const { glUseProgram(m_id); }
};
} // namespace oogl
