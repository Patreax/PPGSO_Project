#include "scene.h"

void Scene::update(float time) {
    camera->update(*this, time);

    lightManager->update(*this);

    auto lightIterator = std::begin(lights);
    while (lightIterator != std::end(lights)) {
        auto obj = lightIterator->get();
        if (!obj->update(*this, time)) {
            lightIterator = lights.erase(lightIterator);
        } else {
            ++lightIterator;
        }
    }



    // Use iterator to update all objects so we can remove while iterating
    auto i = std::begin(objects);

    while (i != std::end(objects)) {
        // Update and remove from list if needed
        auto obj = i->get();
        if (!obj->update(*this, time))
            i = objects.erase(i); // NOTE: no need to call destructors as we store shared pointers in the scene
        else
            ++i;
    }
}

void Scene::render() {

//    glEnable(GL_DEPTH_TEST);
//    glViewport(0, 0, shadowMapWidth, shadowMapHeight);
//    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
//    glClear(GL_DEPTH_BUFFER_BIT);
//
//    shadowMapShader->use();
//    shadowMapShader->setUniform("lightProjection", lightProjection);
//
//    for (auto &obj : objects)
//        obj->render(*this);
//
//
//
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, sceneWidth, sceneHeight);

    glBindFramebuffer(GL_FRAMEBUFFER, postProcessingFBO);

    // Set blue background
    glClearColor(.6f, .8f, 1, 0);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Simply render all objects
    for (auto &obj: objects)
        obj->render(*this);

    for (auto &obj: lights)
        obj->render(*this);


    // Apply post-processing
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    postProcessingShader->use();
    glBindVertexArray(rectVao);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, postProcessingTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

std::vector<Object *> Scene::intersect(const glm::vec3 &position, const glm::vec3 &direction) {
    std::vector<Object *> intersected = {};
    for (auto &object: objects) {
        // Collision with sphere of size object->scale.x
        auto oc = position - object->position;
        auto radius = object->scale.x;
        auto a = glm::dot(direction, direction);
        auto b = glm::dot(oc, direction);
        auto c = glm::dot(oc, oc) - radius * radius;
        auto dis = b * b - a * c;

        if (dis > 0) {
            auto e = sqrt(dis);
            auto t = (-b - e) / a;

            if (t > 0) {
                intersected.push_back(object.get());
                continue;
            }

            t = (-b + e) / a;

            if (t > 0) {
                intersected.push_back(object.get());
                continue;
            }
        }
    }

    return intersected;
}
