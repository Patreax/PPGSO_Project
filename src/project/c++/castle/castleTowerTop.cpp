#include "castleTowerTop.h"
#include "src/project/c++/scene.h"

#include "shaders/phong_frag_glsl.h"
#include "shaders/phong_vert_glsl.h"
#include "src/project/materials/palisadeMaterial.h"

std::unique_ptr<ppgso::Mesh> CastleTowerTop::mesh;
std::unique_ptr<ppgso::Shader> CastleTowerTop::shader;
std::unique_ptr<ppgso::Texture> CastleTowerTop::texture;

CastleTowerTop::CastleTowerTop() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(phong_vert_glsl, phong_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("stone.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("castleTowerTop.obj");

    auto material = std::make_unique<PalisadeMaterial>();
    this->objectMaterial = std::move(material);
}

bool CastleTowerTop::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void CastleTowerTop::render(Scene &scene) {
    shader->use();

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
