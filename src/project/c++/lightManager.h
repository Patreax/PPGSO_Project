#pragma once
#include <memory>
#include <list>
#include <map>
#include <ppgso/ppgso.h>
#include <glm/glm.hpp>

class Scene;

class LightManager {
private:
    void getLightPositions(Scene &scene);
    void getLightColors(Scene &scene);
    void getLightTypes(Scene &scene);

public:
    LightManager() = default;
    LightManager(const LightManager&) = default;
    LightManager(LightManager&&) = default;
    virtual ~LightManager() {};

    static const int globalNumberOfLights = 5;
    int currentNumberOfLights = 5;

    glm::vec3 lightPositions[globalNumberOfLights];
    glm::vec4 lightColors[globalNumberOfLights];
    // 1 - point light
    // 2 - spot light
    int lightType[globalNumberOfLights];


    bool update(Scene &scene);

};
