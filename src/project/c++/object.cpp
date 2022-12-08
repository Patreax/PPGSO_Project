#define GLM_ENABLE_EXPERIMENTAL

#include "object.h"
#include <glm/gtx/euler_angles.hpp>
#include "glm/gtc/matrix_transform.hpp"

void Object::generateModelMatrix() {
    modelMatrix = glm::translate(glm::mat4(1.0f), position)
                  * glm::orientate4(rotation)
                  * glm::scale(glm::mat4(1.0f), scale);
}
