//
// Created by matej on 12/12/22.
//

#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "keyframeAnimation.h"


void KeyframeAnimation::set(std::vector<Keyframe> anim) {
    animation = anim;
    current = 0;
    next = 1;
    time = 0;
    time_next = anim[0].time;
    repeat = false;
}

glm::mat4 KeyframeAnimation::update(float dt) {
    time += dt;
    if(time > time_next){
        time -= time_next;
        time_next = animation[next].time;

        current = next;
        next = (next + 1) % animation.size();

        if(next == 0){
            repeat = true;
        }
    }
    float t = time / time_next;

    glm::vec3 position = glm::lerp(
            animation[current].position,
            animation[next].position,
            t
            );

    glm::vec3 rot_from = animation[current].rotation;
    glm::vec3 rot_to = animation[next].rotation;

    if(rot_from.x < rot_to.x){
        rot_to.x -= deg_180 * 2;
    }
    if(rot_from.y < rot_to.y){
        rot_to.y -= deg_180 * 2;
    }
    if(rot_from.z < rot_to.z){
        rot_to.z -= deg_180 * 2;
    }

    glm::vec3 rotation = glm::lerp(
            rot_from,
            rot_to,
            t
            );

    return glm::translate(glm::mat4(1.0f), position)
           * glm::orientate4(rotation);

/*
    return glm::orientate4(rotation)
           * glm::translate(glm::mat4(1.0f), position);
*/
}

bool KeyframeAnimation::is_done() {
    return repeat;
}

