//
// Created by matej on 12/10/22.
//

#include "knight.h"
/*
#include "knightHelm.h"
#include "knightArm.h"
#include "knightLeg.h"
#include "knightCloak.h"
*/

Knight::Knight() : Object("mouse.obj", "mouse.bmp"){
    using namespace std;
    //unique_ptr<Object> helm = make_unique<KnightHelm>();
    /*
    auto helm = make_unique<KnightHelm>();
    auto left_arm = make_unique<KnightArm>();
    auto right_arm = make_unique<KnightArm>();
    auto left_leg = make_unique<KnightLeg>();
    auto right_leg = make_unique<KnightLeg>();
    auto cloak = make_unique<KnightCloak>();

    right_arm->scale.x = -1;
    right_leg->scale.x = -1;


    children.push_back(move(helm));
    children.push_back(move(left_arm));
    //children.push_back(move(right_arm));
    children.push_back(move(left_leg));
    //children.push_back(move(right_leg));
    children.push_back(move(cloak));
*/
    anim.set({
                     {2,{0,0,0},anim.left},
                     {1,{20,0,0},anim.left},
                     {2,{20,0,0},anim.front},
                     {1,{20,0,20},anim.front},
                     {2,{20,0,20},anim.right},
                     {1,{0,0,20},anim.right},
                     {2,{0,0,20},anim.back},
                     {1,{0,0,0},anim.back}
             });
}

bool Knight::update(Scene &scene, float dt) {

    return Object::update(scene, dt, anim);
}
