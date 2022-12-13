//
// Created by matej on 12/10/22.
//

#ifndef PPGSO_KNIGHT_H
#define PPGSO_KNIGHT_H


#include "object.h"
#include "keyframeAnimation.h"

class Knight : public Object{
public:
    Knight();
    KeyframeAnimation anim;
    bool update(Scene &scene, float dt) override;
};


#endif //PPGSO_KNIGHT_H
