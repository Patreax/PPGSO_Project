#include "pointLight.h"
#include "scene.h"

#include <shaders/light_vert_glsl.h>
#include <shaders/light_frag_glsl.h>

std::unique_ptr<ppgso::Shader> PointLight::shader;
std::unique_ptr<ppgso::Mesh> PointLight::mesh;

PointLight::PointLight() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(light_vert_glsl, light_frag_glsl);
//    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("stone.bmp"));
//    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
}

bool PointLight::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void PointLight::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);

    shader->setUniform("LightColor", lightColor);

    shader->setUniform("Transparency", 0.0f);

//    mesh->render();
}
