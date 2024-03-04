#pragma once

#include "glm/glm.hpp"

struct EntityState {
  glm::vec2 position;
  glm::vec2 size;

  float scale;
  float rotation;
};

namespace EntityFunctions {
  glm::mat4 getModelMatrix(const EntityState& entity);
}