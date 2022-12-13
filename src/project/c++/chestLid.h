
#ifndef PPGSO_CHESTLID_H
#define PPGSO_CHESTLID_H


#include "object.h"
#include "spider.h"

class ChestLid : public Object {
public:
    float age;
    ChestLid();
    virtual bool update(Scene &scene, float dt, glm::mat4 parent);

};


#endif //PPGSO_CHESTLID_H
