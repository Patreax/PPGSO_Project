#include "cannon.h"
#include "scene.h"
#include "ball.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Cannon::mesh;
std::unique_ptr<ppgso::Shader> Cannon::shader;
std::unique_ptr<ppgso::Texture> Cannon::texture;

Cannon::Cannon(int offset) {
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("cannon.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cannon.obj");
    ballsGenerated = 0;
    elapsed = offset;
}

void Cannon::generateBall(Scene &scene) {
    auto obj = std::make_unique<Ball>();
    obj->position = position + glm::vec3 {0, 4, -5};
    scene.objects.push_back(std::move(obj));
    ballsGenerated++;
}

bool Cannon::update(Scene &scene, float dt) {
    generateModelMatrix();
    elapsed += dt;
    if(elapsed / (4.0f) > ballsGenerated){
        generateBall(scene);
    }
    return true;
}

void Cannon::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}
