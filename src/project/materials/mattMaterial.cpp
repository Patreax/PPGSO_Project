#include "mattMaterial.h"

MattMaterial::MattMaterial() {
    ambientComponent = glm::vec4{0.8f, 0.8f, 0.8f, 0.8f};
    diffuseComponent = glm::vec4{5, 5, 5, 5};
    specularComponent = glm::vec4{1.5f, 1.5f, 1.5f, 1.5f};
}

