#include "chest.h"
#include "scene.h"



Chest::Chest() : Object("chest.obj", "chest.bmp"){
    children.push_back(std::make_unique<ChestLid>());
}

bool Chest::update(Scene &scene, float dt) {
    Object::update(scene, dt);
    return true;
}