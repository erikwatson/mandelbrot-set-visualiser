#include "glad/glad.h"
#include "glm/glm.hpp"
#include <iostream>

namespace GraphicsFunctions {
  void drawRectangle(float width, float height) {
    float vertices[] = {
      0.0f, 0.0f, 0.0f,            // Vertex 1: Position
      0.0f, 0.0f,                  // Vertex 1: Texture coordinates (not flipped)

      width, 0.0f, 0.0f,           // Vertex 2: Position
      1.0f, 0.0f,                  // Vertex 2: Texture coordinates (not flipped)

      width, height, 0.0f,         // Vertex 3: Position
      1.0f, 1.0f,                  // Vertex 3: Texture coordinates (not flipped)

      0.0f, 0.0f, 0.0f,            // Vertex 4: Position
      0.0f, 0.0f,                  // Vertex 4: Texture coordinates (not flipped)

      width, height, 0.0f,         // Vertex 5: Position
      1.0f, 1.0f,                  // Vertex 5: Texture coordinates (not flipped)

      0.0f, height, 0.0f,          // Vertex 6: Position
      0.0f, 1.0f                   // Vertex 6: Texture coordinates (not flipped)
    };

    // Render the rectangle
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }

  void drawSubRectangle(float width, float height, float subX, float subY, float subWidth, float subHeight) {
    float vertices[] = {
      0.0f, 0.0f, 0.0f,                  // Vertex 1: Position
      subX, subY + subHeight,            // Vertex 1: Texture coordinates (flipped Y)

      width, 0.0f, 0.0f,                 // Vertex 2: Position
      subX + subWidth, subY + subHeight, // Vertex 2: Texture coordinates (flipped Y)

      width, height, 0.0f,               // Vertex 3: Position
      subX + subWidth, subY,             // Vertex 3: Texture coordinates (flipped Y)

      0.0f, 0.0f, 0.0f,                  // Vertex 4: Position
      subX, subY + subHeight,            // Vertex 4: Texture coordinates (flipped Y)

      width, height, 0.0f,               // Vertex 5: Position
      subX + subWidth, subY,             // Vertex 5: Texture coordinates (flipped Y)

      0.0f, height, 0.0f,                // Vertex 6: Position
      subX, subY                         // Vertex 6: Texture coordinates (flipped Y)
    };

    // Render the rectangle
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 6);
  }

  void drawRectangle(glm::vec2 size) {
    drawRectangle(size.x, size.y);
  };

  void drawSubRectangle(glm::vec2 size, glm::vec2 subPosition, glm::vec2 subSize) {
    drawSubRectangle(
      size.x, size.y, 
      subPosition.x, subPosition.y, 
      subSize.x, subSize.y
    );
  };

  void drawSubRectangle(float width, float height, glm::vec2 subPosition, glm::vec2 subSize) {
    drawSubRectangle(
      width, height, 
      subPosition.x, subPosition.y, 
      subSize.x, subSize.y
    );
  }

  void drawSubRectangle(glm::vec2 size, float subX, float subY, float subWidth, float subHeight) {
    drawSubRectangle(
      size.x, size.y, 
      subX, subY, 
      subWidth, subHeight
    );
  }
}
