//
// Created by senas on 2022. 12. 03..
//

#include <ppgso/ppgso.h>

#include "object.h"

class Water final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

public:
    Water();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};
