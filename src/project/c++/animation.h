//
// Created by matej on 12/13/22.
//

#ifndef PPGSO_ANIMATION_H
#define PPGSO_ANIMATION_H


#include <glm/fwd.hpp>

class Animation {
public:
    virtual glm::mat4 update(float dt) = 0;
    virtual bool is_done() = 0;
};


#endif //PPGSO_ANIMATION_H
