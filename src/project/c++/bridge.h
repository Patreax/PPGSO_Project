#include <ppgso/ppgso.h>

#include "object.h"

class Bridge final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    float elapsed = 0;
    int cycle = 0;
    int animState = 0;
    float angle = 0;

public:
    Bridge();

    virtual float rad(float deg);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};
