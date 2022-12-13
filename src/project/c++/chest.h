
#ifndef PPGSO_CHEST_H
#define PPGSO_CHEST_H


#include "object.h"
#include "chestLid.h"

class Chest final : public Object {
public:
    Chest();

    bool update(Scene &scene, float dt) override;
};

#endif //PPGSO_CHEST_H
