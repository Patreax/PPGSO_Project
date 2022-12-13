#include <glm/glm.hpp>

#include "camera.h"
#include "scene.h"
#include "glm/gtx/euler_angles.hpp"


Camera::Camera(float fow, float ratio, float near, float far) {
    float fowInRad = (ppgso::PI / 180.0f) * fow;

    projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
}

void Camera::update(Scene &scene, float dt) {
//    viewMatrix = lookAt(position, position - back, up);
//    viewMatrix = glm::rotate(glm::mat4{1.0f}, rotation.y, up);
//    viewMatrix = lookAt(position, direction, up);

    //viewMatrix = glm::lookAt(position, position + cameraFront, up);
    //move(scene, dt, scene.cursor.x, scene.cursor.y);
    // move(scene, dt, lastX, lastY);

    static int stage = 0;
    if(current_anim->is_done() || stage == 0){
        stage++;
        switch (stage) {
            case 1:
                anim.set({
                                 {5,{0,-5,-80},anim.back},
                                 {5,{0,-5,-40},anim.back}
                         });
                current_anim = &anim;
                break;
            case 2:
                curve.set(
                        5,
                        {-10, 0, -10},
                        {-5, 10, -10},
                        {5, 10, -10},
                        {10, 0, -10},
                        anim.back
                );
                current_anim = &curve;

        }
    }

    viewMatrix = glm::inverse(current_anim->update(dt));
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

void Camera::move(Scene &scene, float dt, float xpos, float ypos) {

    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.2f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f){
        pitch = 89.0f;
    }
    if (pitch < -89.0f){
        pitch = -89.0f;
    }

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);

    viewMatrix = glm::lookAt(position, position + cameraFront, up);

    float speed = 10.0f * dt;

    if (scene.keyboard[GLFW_KEY_LEFT_SHIFT]){
        speed *= 4;

    }

    if (scene.keyboard[GLFW_KEY_P]) {
        std::cout << "x:" << position.x << " y:" << position.y << " z:" <<position.z;
        std::cout << " yaw: " << yaw << " pitch:" << pitch << "\n";
    }

    if (scene.keyboard[GLFW_KEY_W]) {
        position += speed * cameraFront;
    }
    if (scene.keyboard[GLFW_KEY_S]) {
        position -= speed * cameraFront;
    }
    if (scene.keyboard[GLFW_KEY_A]) {
        position -= speed * glm::normalize(glm::cross(cameraFront, up));;
    }
    if (scene.keyboard[GLFW_KEY_D]) {
        position += speed * glm::normalize(glm::cross(cameraFront, up));;
    }
    if (scene.keyboard[GLFW_KEY_SPACE]) {
        position += speed * up;
    }
    if (scene.keyboard[GLFW_KEY_LEFT_CONTROL]) {
        position -= speed * up;
    }

    // TODO void onCursorPos(double cursorX, double cursorY) override na aktulanu poziciu mysi















//    float sensitivity = 100.0f;
//
//    int width = 1920;
//    int height = 1080;
//
//
//    double u = scene.cursor.x / width;
//    double v = - scene.cursor.y / height;
//
//
//    // Get mouse pick vector in world coordinates
//    auto direction = scene.camera->cast(u, v) * sensitivity;
//
//    double u;
//    double v;
//
//    if (scene.keyboard[GLFW_KEY_W]) {
//        position += speed * glm::normalize(direction);
//    }
//    if (scene.keyboard[GLFW_KEY_S]) {
//        position += speed * glm::normalize(-direction);
//    }
//    if (scene.keyboard[GLFW_KEY_A]) {
//        position += speed * -glm::normalize(glm::cross(direction, up));;
//    }
//    if (scene.keyboard[GLFW_KEY_D]) {
//        position += speed * glm::normalize(glm::cross(direction, up));;
//    }
//
//
//
//    if (scene.cursor.left){
//        bool firstClick = true;
//
//        if (firstClick){
//            u = width / 2;
//            v = height / 2;
//            firstClick = false;
//        }
//
//        u = scene.cursor.x / width;
//        v = - scene.cursor.y / height;
//
//        // Get mouse pick vector in world coordinates
//        auto direction = scene.camera->cast(u, v) * sensitivity;
//
//        viewMatrix = lookAt(position, direction, up);
//    }

}

void Camera::rotate(Scene &scene) {

//    rotation.z = ppgso::PI/4.0f;

}