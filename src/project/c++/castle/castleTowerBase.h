#pragma once

#include "ppgso.h"

#include "src/project/c++/object.h"

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
