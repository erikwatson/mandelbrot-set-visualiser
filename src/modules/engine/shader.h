#pragma once

#include <string>
#include "glad/glad.h"

struct ShaderPrograms {
  GLuint mandelbrot;
};

namespace ShaderFunctions {
  std::string readShaderFile(const std::string& filePath);
  GLuint createAndCompileShader(GLenum type, std::string filePath);
  GLuint createShaderProgram(std::string vertexPath, std::string fragmentPath);
  bool initialise(ShaderPrograms& shaders);
}