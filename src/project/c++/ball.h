#include <ppgso/ppgso.h>

#include "object.h"

class Ball final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    float gravity = 3.2f;
    double speed = 0;
    glm::vec3 direction;

public:
    Ball();

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

