//
// Created by matej on 12/13/22.
//

#include <glm/gtx/compatibility.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "curve.h"
#include "glm/gtc/matrix_transform.hpp"

void Curve::set(float time, glm::vec3 p_0, glm::vec3 p_1, glm::vec3 p_2, glm::vec3 p_3, glm::vec3 direction) {
    max_time = time;
    current_time = 0;
    done = false;
    p0 = p_0;
    p1 = p_1;
    p2 = p_2;
    p3 = p_3;
    rotation = direction;
}

glm::mat4 Curve::update(float dt) {

    current_time += dt;
    if(current_time > max_time){
        current_time = max_time;
        done = true;
    }
    float t = current_time / max_time;

    glm::vec3 p01, p12, p23;
    p01 = glm::lerp(p0, p1, t);
    p12 = glm::lerp(p1, p2, t);
    p23 = glm::lerp(p2, p3, t);

    glm::vec3 p012, p123;
    p012 = glm::lerp(p01, p12, t);
    p123 = glm::lerp(p12, p23, t);

    glm::vec3 p0123;
    p0123 = glm::lerp(p012, p123, t);
    return glm::translate(glm::mat4(1.0f), p0123)
           * glm::orientate4(rotation);
}

bool Curve::is_done() {
    return done;
}


