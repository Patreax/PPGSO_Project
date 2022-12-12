#include "bridge.h"
#include "scene.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

std::unique_ptr<ppgso::Mesh> Bridge::mesh;
std::unique_ptr<ppgso::Shader> Bridge::shader;
std::unique_ptr<ppgso::Texture> Bridge::texture;

Bridge::Bridge() {
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP("wood.bmp"));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>("bridge.obj");
}

bool Bridge::update(Scene &scene, float dt) {
    elapsed += dt;
    if(int(elapsed) / 10 > cycle){
        cycle++;
        animState++;
        if(animState > 3)
            animState = 0;
    }
    if(animState == 1){
        angle += 9 * dt;
    }
    if(animState == 3){
        angle -= 9 * dt;
    }
    rotation.x = rad(angle);
    generateModelMatrix();
    return true;
}

void Bridge::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();
}

float Bridge::rad(float deg) {
    return deg * (ppgso::PI / 180);
}