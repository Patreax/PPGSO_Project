//
// Created by PC on 2022. 12. 04..
//
#include <ppgso/ppgso.h>

#include "object.h"

class RiverGenerator final : public Object {
private:
    float elapsed;
    int boatsGenerated;
    int logsGenerated;

public:
    RiverGenerator();

    virtual void generateBoat(Scene &scene);

    virtual void generateLog(Scene &scene);

    bool update(Scene &scene, float dt) override;

    void render(Scene &scene) override;
};

