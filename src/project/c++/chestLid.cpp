#include "chestLid.h"
#include "scene.h"


ChestLid::ChestLid() : Object("chest_lid.obj", "chest.bmp"){
    children.push_back(std::make_unique<Spider>());
   position = {0, 55, -31};
   age = 0;
}


bool ChestLid::update(Scene &scene, float dt, glm::mat4 parent) {
    // add rotation
    age += dt;
    rotation.x = sin(age) - ppgso::PI/3;
    Object::update(scene, dt, parent);
}
