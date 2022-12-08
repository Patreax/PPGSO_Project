#pragma once

#include <ppgso/ppgso.h>
#include <glm/glm.hpp>

class ObjectMaterial {
public:
    ObjectMaterial();

    glm::vec4 ambientComponent{1.0f, 1.0f, 1.0f, 1.0f};
    glm::vec4 diffuseComponent{1.0f, 1.0f, 1.0f, 1.0f};
    glm::vec4 specularComponent{1.0f, 1.0f, 1.0f, 1.0f};
};
