//
// Created by PC on 2022. 12. 04..
//

#include "boat.h"
#include "scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Boat::mesh;
std::unique_ptr<ppgso::Shader> Boat::shader;
std::unique_ptr<ppgso::Texture> Boat::texture;


Boat::Boat() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("wood.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("boat.obj");
    offset = 10.0f * (double)rand()/(double)RAND_MAX - 5.0f;
    rotation.z = (-135.0f * ppgso::PI / 180);
    scale = glm::vec3{2,2,2};
    position = glm::vec3{-100, -16, -35};
    position.x += 1.5 * offset;
    position.z += offset;
    centerZ = position.z;
    speed = 5.0f;

}

bool Boat::update(Scene &scene, float dt) {
    elapsed += dt;
    position.x = position.x + speed * dt;
    position.z = centerZ + sin(elapsed + offset);
    generateModelMatrix();
    if(position.x > 100)
        return false;
    return true;
}

void Boat::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}
