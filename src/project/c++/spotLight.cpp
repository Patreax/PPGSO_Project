#include "spotLight.h"
#include "scene.h"

#include <shaders/light_vert_glsl.h>
#include <shaders/light_frag_glsl.h>

std::unique_ptr<ppgso::Shader> SpotLight::shader;
std::unique_ptr<ppgso::Mesh> SpotLight::mesh;
//std::unique_ptr<ppgso::Texture> SpotLight::texture;

SpotLight::SpotLight() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(light_vert_glsl, light_frag_glsl);
//    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("stone.bmp"));
//    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");
}

bool SpotLight::update(Scene &scene, float dt) {
//    position.x = sin(time*2)*2;

//    if (attachedPosition != nullptr){
//        this->position = attachedPosition + glm::vec3{2, 7, -5};
//    }

//    time += dt;
//    this->position.x = cos(time);
//    this->position.z = sin(time);

    generateModelMatrix();
    return true;
}

void SpotLight::render(Scene &scene) {
    shader->use();

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);

    shader->setUniform("LightColor", lightColor);

    shader->setUniform("Transparency", 0.0f);

//    mesh->render();
}
