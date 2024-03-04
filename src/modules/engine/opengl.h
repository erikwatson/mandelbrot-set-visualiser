#pragma once
#include <string>
#include "glad/glad.h"
#include "world.h"

namespace OpenGLFunctions {
  bool initialise(int width, int height);
  bool initialiseBuffers(GLuint& VAO, GLuint& VBO, GLuint& basicShaderProgram);
  bool initialiseTexture(std::string path, GLuint& texture);
  void bindTexture(GLuint texture, GLuint basicShaderProgram);
  void bindMandelbrotUniforms(GLuint shaderProgram, float timeValue, glm::vec2 resolution, float zoom, glm::vec2 offset);
}