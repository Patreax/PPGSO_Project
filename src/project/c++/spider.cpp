#include "spider.h"

Spider::Spider() : Object("spider.obj", "spider.bmp"){
    scale = {100,100,100};
    position = {0, 25, 30};
    age = 0;
}

float lerp(float a, float b, float t){
    return t * b + (1 - t) * a;
}

bool Spider::update(Scene &scene, float dt, glm::mat4 parent) {
    // add movement
    const float time = 1;
    age += dt;
    if(age > 4 * time){
        age -= 4 * time;
    }
    const float pos_left = -40;
    const float pos_right = 40;
    const float rot_left = ppgso::PI / 2;
    const float rot_right = -ppgso::PI / 2;

    if(age < time){
        float t = age / time;
        position.x = lerp(pos_left, pos_right, t);
        rotation.z = rot_left;
    }
    else if(age < 2 * time){
        float t = (age - time) / time;
        position.x = pos_right;
        rotation.z = lerp(rot_left, rot_right, t);
    }
    else if(age < 3 * time){
        float t = (age - 2 * time) / time;
        position.x = lerp(pos_right, pos_left, t);
        rotation.z = rot_right;
    }
    else {
        float t = (age - 3 * time) / time;
        position.x = pos_left;
        rotation.z = lerp(rot_right, rot_left, t);
    }

    Object::update(scene, dt, parent);
    return true;
}
