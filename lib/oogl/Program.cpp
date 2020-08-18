#include "Program.hpp"

#include <fstream>

namespace fs = std::filesystem;

namespace oogl {
Shader::Shader(const std::string &source, GLenum type) : Shader(type) {
  const char *source_c_str = source.c_str();
  glShaderSource(m_id, 1, &source_c_str, nullptr);
  glCompileShader(m_id);
}

std::string read_file_contents(const fs::path &source_file) {
  std::ifstream source_stream;
  source_stream.exceptions(std::ios::badbit | std::ios::failbit);
  source_stream.open(source_file);
  std::stringstream contents;
  contents << source_stream.rdbuf();
  return contents.str();
}

Shader::Shader(const fs::path &source_file, GLenum type)
    : Shader(read_file_contents(source_file), type){};

void attach_and_link(const std::vector<Shader> &shaders, const GLuint id) {
  for (const auto &shader : shaders) {
    glAttachShader(id, shader.id());
  }
  glLinkProgram(id);
  for (const auto &shader : shaders) {
    glDetachShader(id, shader.id());
  }
}

Program::Program(const std::vector<Shader> &shaders) : Program() {
  attach_and_link(shaders, m_id);
};

Program::Program(const std::map<GLenum, fs::path> &shader_sources) : Program() {
  std::vector<Shader> shaders;
  for (const auto &shader_source : shader_sources) {
    shaders.emplace_back(shader_source.second, shader_source.first);
  }
  attach_and_link(shaders, m_id);
};

} // namespace oogl
