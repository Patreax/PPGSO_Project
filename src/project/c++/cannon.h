#include <ppgso/ppgso.h>

#include "object.h"

class Cannon final : public Object {
private:
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;
    float elapsed;
    int ballsGenerated;

public:
    Cannon(int offset);

    virtual void generateBall(Scene &scene);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

