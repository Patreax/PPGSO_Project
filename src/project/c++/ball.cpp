#include "ball.h"
#include "scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Ball::mesh;
std::unique_ptr<ppgso::Shader> Ball::shader;
std::unique_ptr<ppgso::Texture> Ball::texture;

Ball::Ball() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("cannonball.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");
    speed = 10 * (double)rand()/(double)RAND_MAX + 40;
    direction = glm::vec3 {0, 0.5, -1};
    scale = glm::vec3 {.5, .5, .5};
}

bool Ball::update(Scene &scene, float dt) {
    generateModelMatrix();
    position += direction * glm::vec3 {speed * dt, speed * dt, speed * dt};
    position += glm::vec3 {0, dt * -gravity, 0};
    // speed -= .0001;
    if (speed < 0)
        speed = 0;
    // position.y -= dt * gravity;
    gravity += .5f;
    if (position.y < -20) {
        return false;
    }
    return true;
}

void Ball::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}
