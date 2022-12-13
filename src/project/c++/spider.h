//
// Created by matej on 11/29/22.
//

#ifndef PPGSO_SPIDER_H
#define PPGSO_SPIDER_H


#include "object.h"

class Spider : public Object{
public:
    Spider();
    float age;
    virtual bool update(Scene &scene, float dt, glm::mat4 parent);
};


#endif //PPGSO_SPIDER_H
