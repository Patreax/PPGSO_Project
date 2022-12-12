#pragma once

#include <memory>
#include <list>
#include <map>

#include <glm/glm.hpp>
#include "objectMaterial.h"

class Scene;

class Object {
public:
    Object() = default;

    Object(const Object &) = default;

    Object(Object &&) = default;

    virtual ~Object() {};

    virtual bool update(Scene &scene, float dt) = 0;

    virtual void render(Scene &scene) = 0;

    void renderShadows(Scene &scene, std::shared_ptr<ppgso::Shader> shader);


    // Object properties
    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale{1, 1, 1};
    glm::mat4 modelMatrix{1};

    std::unique_ptr<ObjectMaterial> objectMaterial;

protected:
    void generateModelMatrix();
};
