#include "lightManager.h"
#include "spotLight.h"
#include "scene.h"
#include "pointLight.h"

//LightManager::LightManager(){
//
//}

bool LightManager::update(Scene &scene) {
//    currentNumberOfLights = (sizeof(scene.lights) / sizeof(Light));

    getLightPositions(scene);
    getLightColors(scene);
    getLightTypes(scene);

    this->currentNumberOfLights = scene.lights.size();
}

void LightManager::getLightPositions(Scene &scene) {
    int i = 0;
    for (auto &light: scene.lights) {
        this->lightPositions[i] = light->position;
        ++i;
    }
}

void LightManager::getLightColors(Scene &scene) {
    int i = 0;
    for (auto &light: scene.lights) {
        this->lightColors[i] = light->lightColor;
        ++i;
    }
}

void LightManager::getLightTypes(Scene &scene) {
    int i = 0;
    for (auto &light: scene.lights) {
        if (dynamic_cast<PointLight *>(light.get()) != nullptr) {
            this->lightType[i] = 1;
        } else if (dynamic_cast<SpotLight *>(light.get()) != nullptr) {
            this->lightType[i] = 2;
        }
        ++i;
    }
}