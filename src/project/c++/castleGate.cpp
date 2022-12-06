#include "castleGate.h"
#include "scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> CastleGate::mesh;
std::unique_ptr<ppgso::Shader> CastleGate::shader;
std::unique_ptr<ppgso::Texture> CastleGate::texture;

CastleGate::CastleGate() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("rock.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("castleGate.obj");
}

bool CastleGate::update(Scene &scene, float dt) {
    generateModelMatrix();
    return true;
}

void CastleGate::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}
