#include "glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "entity.h"

namespace EntityFunctions {
  glm::mat4 getModelMatrix(const EntityState& entity) {
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(entity.position.x, entity.position.y, 0.0f));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(entity.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(entity.scale, entity.scale, 1.0f));

    return modelMatrix;
  }
}