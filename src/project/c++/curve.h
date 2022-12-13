//
// Created by matej on 12/13/22.
//

#ifndef PPGSO_CURVE_H
#define PPGSO_CURVE_H


#include <glm/vec3.hpp>
#include <glm/fwd.hpp>
#include <vector>
#include "animation.h"

class Curve : public Animation{
public:
    void set(float time,
             glm::vec3 p_0,
             glm::vec3 p_1,
             glm::vec3 p_2,
             glm::vec3 p_3,
             glm::vec3 direction
    );

    bool is_done();
    glm::mat4 update(float dt);

    float current_time, max_time;
    bool done;
    glm::vec3 p0;
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;
    glm::vec3 rotation;
};


#endif //PPGSO_CURVE_H
