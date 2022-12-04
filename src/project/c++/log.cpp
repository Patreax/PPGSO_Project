//
// Created by senas on 2022. 12. 03..
//

#include "log.h"
#include "scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Log::mesh;
std::unique_ptr<ppgso::Shader> Log::shader;
std::unique_ptr<ppgso::Texture> Log::texture;

Log::Log() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("log.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("log.obj");
    position = glm::vec3{-100, -16, -35};
    double s = (double)rand()/ (double)RAND_MAX;
    offset = 10.0f * (double)rand()/(double)RAND_MAX - 5.0f;
    scale = glm::vec3 {s * .2f, s * .2f, s * .2f} + glm::vec3 {.5f,.5f,.5f};
    position.x += offset;
    position.z += offset;
    speed = .1f;
}

bool Log::update(Scene &scene, float dt) {
    position.x = position.x + speed;
    generateModelMatrix();
    if(position.x > 100)
        return false;
    return true;
}

void Log::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}
