#include "glad/glad.h"
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
#include "world.h"

namespace OpenGLFunctions {
  bool initialise(int width, int height) {
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return true;
  }

  bool initialiseBuffers(GLuint& VAO, GLuint& VBO, GLuint& basicShaderProgram) {
    // Set up vertex arrays and buffers 
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    GLint aPosLocation = glGetAttribLocation(basicShaderProgram, "aPos");
    GLint aTexCoordsLocation = glGetAttribLocation(basicShaderProgram, "aTexCoords");
    
    // Position attribute (3 floats)
    glVertexAttribPointer(aPosLocation, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(aPosLocation);

    // Texture coordinate attribute (2 floats)
    glVertexAttribPointer(aTexCoordsLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(aTexCoordsLocation);

    return true;
  }

  bool initialiseTexture(std::string path, GLuint& texture) {
    SDL_Surface* surface = IMG_Load(path.c_str());

    if (!surface) {
      std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
      return false;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Specify the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Generate the texture from the SDL_Surface
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Clean up the SDL_Surface
    SDL_FreeSurface(surface);
    
    return true;
  }

  void bindTexture(GLuint texture, GLuint basicShaderProgram) {
    // Activate the texture unit
    glActiveTexture(GL_TEXTURE0);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, texture);

    // Set the uniform for the texture in the shader
    int textureUniform = glGetUniformLocation(basicShaderProgram, "yourTexture");
    glUniform1i(textureUniform, 0); // 0 corresponds to the texture unit
  }

  void bindMandelbrotUniforms(GLuint shaderProgram, float timeValue, glm::vec2 resolution, float zoom, glm::vec2 position) {
    GLuint timeLocation = glGetUniformLocation(shaderProgram, "iTime");
    GLuint resolutionLocation = glGetUniformLocation(shaderProgram, "iResolution");
    GLuint zoomLocation = glGetUniformLocation(shaderProgram, "iZoom");
    GLuint positionLocation = glGetUniformLocation(shaderProgram, "iPosition");

    glUniform1f(timeLocation, timeValue);
    glUniform2f(resolutionLocation, resolution.x, resolution.y);
    glUniform1f(zoomLocation, zoom);
    glUniform2f(positionLocation, position.x, position.y);
  }
}