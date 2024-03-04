#include "glad/glad.h"
#include <string>
#include <fstream>
#include <iostream>

struct ShaderPrograms {
  GLuint mandelbrot;
};

namespace ShaderFunctions {
  std::string readShaderFile(const std::string& filePath) {
    std::string shaderSource;
    std::ifstream fileStream(filePath, std::ios::in);

    if (fileStream.is_open()) {
      std::string line = "";

      while (getline(fileStream, line)) {
        shaderSource += line + "\n";
      }

      fileStream.close();
    } else {
      std::cerr << "Failed to open file: " << filePath << std::endl;
    }

    return shaderSource;
  }

  GLuint createAndCompileShader(GLenum type, std::string filePath) {
    std::string shaderSource = readShaderFile(filePath);
    const char* source = shaderSource.c_str();

    std::cerr << source << std::endl;

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
      char infoLog[512];
      glGetShaderInfoLog(shader, 512, nullptr, infoLog);
      std::cerr << "Shader compilation error: " << infoLog << std::endl;
    }

    return shader;
  }

  GLuint createShaderProgram(std::string vertexPath, std::string fragmentPath) {
    GLuint vertexShader = createAndCompileShader(GL_VERTEX_SHADER, vertexPath);
    GLuint fragmentShader = createAndCompileShader(GL_FRAGMENT_SHADER, fragmentPath);
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for shader program linking errors
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    
    if (!success) {
      char infoLog[512];
      glGetProgramInfoLog(program, 512, nullptr, infoLog);
      std::cerr << "Shader program linking error: " << infoLog << std::endl;
    }

    // dispose of the shaders, no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
  }

  bool initialise(ShaderPrograms& shaders) {
    std::string basicVertexShaderPath = "./src/shaders/vertex/basic.vert";
    std::string mandelbrotFragmentShaderPath = "./src/shaders/fragment/mandelbrot.frag";
  
    shaders.mandelbrot = createShaderProgram(basicVertexShaderPath, mandelbrotFragmentShaderPath);

    return true;
  }
}