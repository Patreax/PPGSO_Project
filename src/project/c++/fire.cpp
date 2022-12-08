#include "fire.h"
#include "scene.h"
#include "src/project/materials/glossyMaterial.h"
#include "shaders/light_vert_glsl.h"
#include "shaders/light_frag_glsl.h"

#include <shaders/phong_vert_glsl.h>
#include <shaders/phong_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Fire::mesh;
std::unique_ptr<ppgso::Shader> Fire::shader;
std::unique_ptr<ppgso::Texture> Fire::texture;

Fire::Fire() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(light_vert_glsl, light_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("fire-red.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("fire.obj");
}

bool Fire::update(Scene &scene, float dt) {
    time += dt;
    this->position.y = (sin(time * 3) - 19) / 2;
    this->rotation.z = time;
    this->lightColor.g = glm::clamp(abs(sin(time)) - 0.7, 0.0, 1.0);
    generateModelMatrix();
    return true;
}

void Fire::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);

    shader->setUniform("LightColor", lightColor);

    shader->setUniform("Transparency", 0.0f);

    mesh->render();
}
