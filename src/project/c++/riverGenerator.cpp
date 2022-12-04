//
// Created by PC on 2022. 12. 04..
//

#include "riverGenerator.h"
#include "scene.h"
#include "boat.h"
#include "log.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

RiverGenerator::RiverGenerator() {
    boatsGenerated = 0;
    logsGenerated = 0;
}

void RiverGenerator::generateBoat(Scene &scene) {
    auto obj = std::make_unique<Boat>();
    scene.objects.push_back(std::move(obj));
    boatsGenerated++;
}

void RiverGenerator::generateLog(Scene &scene) {
    auto obj = std::make_unique<Log>();
    scene.objects.push_back(std::move(obj));
    logsGenerated++;
}

bool RiverGenerator::update(Scene &scene, float dt) {
    elapsed += dt;
    if(elapsed / 6.0f > boatsGenerated){
        generateBoat(scene);
    }
    if((elapsed + 3) / 6.0f > logsGenerated){
        generateLog(scene);
    }
    //generateModelMatrix();
    return true;
}

void RiverGenerator::render(Scene &scene) {
    return;
}