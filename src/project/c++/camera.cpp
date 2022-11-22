#include <glm/glm.hpp>

#include "camera.h"
#include "scene.h"
#include "glm/gtx/euler_angles.hpp"


Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI / 180.0f) * fow;

    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}

void Camera::update(Scene &scene) {
//    viewMatrix = lookAt(position, position - back, up);
//    viewMatrix = glm::rotate(glm::mat4{1.0f}, rotation.y, up);
//    viewMatrix = lookAt(position, direction, up);
    move(scene);
}

glm::vec3 Camera::cast(double u, double v) {
    // Create point in Screen coordinates
    glm::vec4 screenPosition{u, v, 0.0f, 1.0f};

    // Use inverse matrices to get the point in world coordinates
    auto invProjection = glm::inverse(projectionMatrix);
    auto invView = glm::inverse(viewMatrix);

    // Compute position on the camera plane
    auto planePosition = invView * invProjection * screenPosition;
    planePosition /= planePosition.w;

    // Create direction vector
    auto direction = glm::normalize(planePosition - glm::vec4{position, 1.0f});
    return glm::vec3{direction};
}

void Camera::move(Scene &scene) {
    float speed = 0.01f;
    float sensitivity = 100.0f;

    int width = 1920;
    int height = 1080;


//    double u = scene.cursor.x / width;
//    double v = - scene.cursor.y / height;
//
//
//    // Get mouse pick vector in world coordinates
//    auto direction = scene.camera->cast(u, v) * sensitivity;

    double u;
    double v;

    if (scene.keyboard[GLFW_KEY_W]) {
        position += speed * glm::normalize(direction);
    }
    if (scene.keyboard[GLFW_KEY_S]) {
        position += speed * glm::normalize(-direction);
    }
    if (scene.keyboard[GLFW_KEY_A]) {
        position += speed * -glm::normalize(glm::cross(direction, up));;
    }
    if (scene.keyboard[GLFW_KEY_D]) {
        position += speed * glm::normalize(glm::cross(direction, up));;
    }



    if (scene.cursor.left){
        bool firstClick = true;

        if (firstClick){
            u = width / 2;
            v = height / 2;
            firstClick = false;
        }

        u = scene.cursor.x / width;
        v = - scene.cursor.y / height;

        // Get mouse pick vector in world coordinates
        auto direction = scene.camera->cast(u, v) * sensitivity;

        viewMatrix = lookAt(position, direction, up);
    }

}

void Camera::rotate(Scene &scene) {

//    rotation.z = ppgso::PI/4.0f;

}