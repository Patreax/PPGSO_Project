//
// Created by PC on 2022. 11. 29..
//

#include "water.h"
#include "scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Water::mesh;
std::unique_ptr<ppgso::Shader> Water::shader;
std::unique_ptr<ppgso::Texture> Water::texture;

Water::Water() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("water.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("ground.obj");
    rotation.z = 20.57f;
}

bool Water::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Water::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Transparency", 0.5f);
    shader->setUniform("Texture", *texture);

    mesh->render();
}
