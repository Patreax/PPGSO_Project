#include "torch.h"
#include "scene.h"
#include "src/project/materials/glossyMaterial.h"

#include <shaders/phong_vert_glsl.h>
#include <shaders/phong_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Torch::mesh;
std::unique_ptr<ppgso::Shader> Torch::shader;
std::unique_ptr<ppgso::Texture> Torch::texture;

Torch::Torch() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(phong_vert_glsl, phong_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("torch.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("torch.obj");

    auto material = std::make_unique<GlossyMaterial>();
    this->objectMaterial = std::move(material);
}

bool Torch::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void Torch::render(Scene &scene) {
    shader->use();

    // Uniform for materials

    shader->setUniform("AmbientComponent", this->objectMaterial->ambientComponent);
    shader->setUniform("DiffuseComponent", this->objectMaterial->diffuseComponent);
    shader->setUniform("SpecularComponent", this->objectMaterial->specularComponent);

    shader->setUniform("CurrentNumberOfLights", scene.lightManager->currentNumberOfLights);
    shader->setUniform("LightPositions", scene.lightManager->lightPositions, scene.lightManager->currentNumberOfLights);
    shader->setUniform("LightColors", scene.lightManager->lightColors, scene.lightManager->currentNumberOfLights);
    shader->setUniform("LightTypes", scene.lightManager->lightType, scene.lightManager->currentNumberOfLights);

    shader->setUniform("CameraPosition", scene.camera->position);
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}
