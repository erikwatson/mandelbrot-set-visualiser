#pragma once

#include "glm/glm.hpp"

namespace GraphicsFunctions {
  void drawRectangle(float width, float height);
  void drawRectangle(glm::vec2 size);

  void drawSubRectangle(float width, float height, float subX, float subY, float subWidth, float subHeight);
  void drawSubRectangle(float width, float height, glm::vec2 subPosition, glm::vec2 subSize);
  void drawSubRectangle(glm::vec2 size, glm::vec2 subPosition, glm::vec2 subSize);
  void drawSubRectangle(glm::vec2 size, float subX, float subY, float subWidth, float subHeight);
}