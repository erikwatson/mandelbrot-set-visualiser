#pragma once

#include "glm/glm.hpp"
#include <vector>
#include "entity.h"

struct WorldState {
  glm::vec2 position;
  float scale;
  float rotation;
  std::vector<EntityState> entities;
};

namespace WorldFunctions {
  glm::mat4 getModelMatrix(EntityState& entity);
}