#pragma once

#include <memory>
#include <list>
#include <map>

#include <glm/glm.hpp>

class Scene;

class Light {
public:
    Light() = default;

    Light(const Light &) = default;

    Light(Light &&) = default;

    virtual ~Light() {};

    virtual bool update(Scene &scene, float dt) = 0;

    virtual void render(Scene &scene) = 0;

    // Light properties
    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale{1, 1, 1};
    glm::mat4 modelMatrix{1};

    glm::vec4 lightColor;

protected:
    void generateModelMatrix();

};
