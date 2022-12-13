#define GLM_ENABLE_EXPERIMENTAL

#include "object.h"
#include "scene.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/euler_angles.hpp>
#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

/*
std::unique_ptr<ppgso::Mesh> Object::mesh;
std::unique_ptr<ppgso::Texture> Object::texture;
 */

std::unique_ptr<ppgso::Shader> Object::shader;

std::unordered_map<std::string, ppgso::Mesh*> Object::meshes;
std::unordered_map<std::string, ppgso::Texture*> Object::textures;



Object::Object(std::string mesh_file, std::string texture_file) {
    if (!shader) shader = std::make_unique<ppgso::Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    /*
    if (!texture) texture = std::make_unique<ppgso::Texture>(ppgso::image::loadBMP(texture_file));
    if (!mesh) mesh = std::make_unique<ppgso::Mesh>(mesh_file);
     */
    if(meshes.find(mesh_file) == meshes.end()) meshes[mesh_file] = new ppgso::Mesh(mesh_file);
    if(textures.find(texture_file) == textures.end()) textures[texture_file] = new ppgso::Texture(ppgso::image::loadBMP(texture_file));

    mesh = meshes[mesh_file];
    texture = textures[texture_file];
}

void Object::generateModelMatrix() {
    generateModelMatrix(glm::mat4(1.0f));
}

void Object::generateModelMatrix(glm::mat4 parent){
    modelMatrix = parent
                  * glm::translate(glm::mat4(1.0f), position)
                  * glm::orientate4(rotation)
                  * glm::scale(glm::mat4(1.0f), scale);
}

void Object::render(Scene &scene) {
    shader->use();

    shader->setUniform("LightDirection", scene.lightDirection);

    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();

    for (auto &child:children) {
        child->render(scene);
    }
}

bool Object::update(Scene &scene, float dt) {
    generateModelMatrix();
    for (auto &child:children){
        child->update(scene, dt, modelMatrix);
    }
    return true;
}

bool Object::update(Scene &scene, float dt, glm::mat4 parent) {
    generateModelMatrix(parent);
    for (auto &child:children){
        child->update(scene, dt, modelMatrix);
    }
    return true;
}

bool Object::update(Scene &scene, float dt, KeyframeAnimation &anim) {
    generateModelMatrix();
    modelMatrix = modelMatrix * anim.update(dt);
    for (auto &child:children){
        child->update(scene, dt, modelMatrix);
    }
    return true;
}

void Object::renderShadows(Scene &scene, std::shared_ptr<ppgso::Shader> shader) {
    shader->use();
    shader->setUniform("model", this->modelMatrix);
}

