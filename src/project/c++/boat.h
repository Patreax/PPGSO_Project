//
// Created by PC on 2022. 12. 04..
//
#include <ppgso/ppgso.h>

#include "object.h"

class Boat final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    float offset;
    float speed = 0;
    float elapsed = 0;
    float centerZ;

public:
    Boat();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

