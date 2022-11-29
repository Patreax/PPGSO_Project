#pragma once
#include <ppgso/ppgso.h>

#include "object.h"

class CastleTowerBase final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:
    CastleTowerBase();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};
