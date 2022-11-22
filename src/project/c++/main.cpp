#include <iostream>
#include <list>

#include <ppgso/ppgso.h>

#include "camera.h"
#include "scene.h"
#include "castle.h"

const unsigned int SIZE = 512;

const unsigned int WIDTH = 1920;
const unsigned int HEIGHT = 1080;

class SceneWindow : public ppgso::Window {
private:
    Scene scene;

    /*!
     * Reset and initialize the game scene
     * Creating unique smart pointers to objects that are stored in the scene object list
     */
    void initScene() {
        scene.objects.clear();

        // Create a camera
        auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 100.0f);
        camera->position.z = -55.0f;
        scene.camera = std::move(camera);

        auto castle = std::make_unique<Castle>();
        castle->position.y = -6;
        castle->rotation.x = -45;
        scene.objects.push_back(std::move(castle));
    }

public:

    /*!
     * Construct custom game window
     */
    SceneWindow() : Window{"demo", WIDTH, HEIGHT} {
        //hideCursor();
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

        // Initialize OpenGL state
        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Enable polygon culling
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        initScene();
    }

    void onKey(int key, int scanCode, int action, int mods) override {
        scene.keyboard[key] = action;
    }

    /*!
     * Handle cursor position changes
     * @param cursorX Mouse horizontal position in window coordinates
     * @param cursorY Mouse vertical position in window coordinates
     */
    void onCursorPos(double cursorX, double cursorY) override {
        scene.cursor.x = cursorX;
        scene.cursor.y = cursorY;
    }


    void onMouseButton(int button, int action, int mods) override {
        if(button == GLFW_MOUSE_BUTTON_LEFT) {
            scene.cursor.left = action == GLFW_PRESS;

            if (scene.cursor.left) {

                scene.camera->rotate(scene);

                // Convert pixel coordinates to Screen coordinates
                double u = (scene.cursor.x / width - 0.5f) * 2.0f;
                double v = - (scene.cursor.y / height - 0.5f) * 2.0f;

                // Get mouse pick vector in world coordinates
                auto direction = scene.camera->cast(u, v);
                auto position = scene.camera->position;

                // Get all objects in scene intersected by ray
                auto picked = scene.intersect(position, direction);

                // Go through all objects that have been picked
                for (auto &obj: picked) {
                    // Pass on the click event
//                    obj->onClick(scene);
                }
            }
        }
        if(button == GLFW_MOUSE_BUTTON_RIGHT) {
            scene.cursor.right = action == GLFW_PRESS;
        }



    }

    /*!
     * Window update implementation that will be called automatically from pollEvents
     */
    void onIdle() override {
        // Track time
        static auto time = (float) glfwGetTime();

        // Compute time delta
        float dt = (float) glfwGetTime() - time;

        time = (float) glfwGetTime();

//        // Set blue background
        glClearColor(.6f, .8f, 1, 0);
//         Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update and render all objects
        scene.update(dt);
        scene.render();
    }
};

int main() {
    // Initialize our window
    SceneWindow window;

    // Main execution loop
    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}
