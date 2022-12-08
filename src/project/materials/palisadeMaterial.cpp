#include "palisadeMaterial.h"

PalisadeMaterial::PalisadeMaterial() {
    ambientComponent = glm::vec4{1.5f, 1.5f, 1.5f, 1.5f};
    diffuseComponent = glm::vec4{1.2f, 1.2f, 1.2f, 1.2f};
    specularComponent = glm::vec4{1.7f, 1.7f, 1.7f, 1.7f};
}

