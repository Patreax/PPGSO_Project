#pragma once

#include <ppgso/ppgso.h>

#include "spotLight.h"
#include "pointLight.h"

class Fire final : public PointLight {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:
    Fire();

    float time = 0;

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};