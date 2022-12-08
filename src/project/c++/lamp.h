#pragma once

#include <ppgso/ppgso.h>

#include "object.h"

class Lamp final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    float time = 0;
public:
    Lamp();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};