//
// Created by matej on 12/12/22.
//

#ifndef PPGSO_KEYFRAMEANIMATION_H
#define PPGSO_KEYFRAMEANIMATION_H


#include <vector>
#include <glm/vec3.hpp>
#include <glm/fwd.hpp>
#include "ppgso.h"
#include "animation.h"

class KeyframeAnimation : public Animation {
    const float deg_180 = ppgso::PI;
    const float deg_90 = ppgso::PI / 2;


public:
    typedef struct {
        float time;
        glm::vec3 position;
        glm::vec3 rotation;
    } Keyframe;

    void set(std::vector<Keyframe> anim);

    std::vector<Keyframe> animation;
    int current, next;
    float time, time_next;
    bool repeat;

    bool is_done();
    glm::mat4 update(float dt);

    const glm::vec3 front = {0,0,0};
    const glm::vec3 left = {0,0,deg_90};
    const glm::vec3 back = {0,0,deg_180};
    const glm::vec3 right = {0,0,-deg_90};



};


#endif //PPGSO_KEYFRAMEANIMATION_H
