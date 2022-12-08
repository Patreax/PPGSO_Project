#include "glossyMaterial.h"

GlossyMaterial::GlossyMaterial() {
    ambientComponent = glm::vec4{1.5f, 1.5f, 1.5f, 1.5f};
    diffuseComponent = glm::vec4{10, 10, 10, 10};
    specularComponent = glm::vec4{10, 10, 10, 10};
}

