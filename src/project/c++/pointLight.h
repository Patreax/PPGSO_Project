#pragma once
#include <ppgso/ppgso.h>

#include "object.h"
#include "light.h"

class PointLight : public Light {
private:
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Mesh> mesh;
//    static std::unique_ptr<ppgso::Texture> texture;

    float time = 0;

public:
    PointLight();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};