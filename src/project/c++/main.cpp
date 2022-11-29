#include <iostream>
#include <list>

#include <ppgso/ppgso.h>

#include "camera.h"
#include "scene.h"
#include "castle.h"
#include "castleGate.h"
#include "castleWall.h"
#include "castleTowerBase.h"
#include "castleTowerTop.h"
#include "clock.h"
#include "hourHand.h"

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

        // Gate
        auto castleGate = std::make_unique<CastleGate>();
        castleGate->position = {0, -6, 0};

        // Wall
        auto castleWallLeft = std::make_unique<CastleWall>();
        castleWallLeft->position = castleGate->position + glm::vec3{25, 0, 25};
        castleWallLeft->rotation = {0, 0, 1.6f};

        auto castleWallRight = std::make_unique<CastleWall>();
        castleWallRight->position = castleGate->position + glm::vec3{-25, 0, 25};
        castleWallRight->rotation = {0, 0, 1.6f};

        // towerBase
        auto castleTowerBase = std::make_unique<CastleTowerBase>();
        castleTowerBase->position = castleGate->position + glm::vec3{-30, -1, 0};

        auto castleTowerBase1 = std::make_unique<CastleTowerBase>();
        castleTowerBase1->position = castleGate->position + glm::vec3{30, -1, 0};
        auto castleTowerTop1 = std::make_unique<CastleTowerTop>();
        castleTowerTop1->position = castleTowerBase1->position + glm::vec3{0, 13, 0};

        // towerTop
        auto castleTowerTop = std::make_unique<CastleTowerTop>();
        castleTowerTop->position = castleTowerBase->position + glm::vec3{0, 13, 0};

        // clock
        auto clock = std::make_unique<Clock>();
        clock->position = {0, 0, -15};
        clock->scale = {0.1f, 0.1f, 0.1f};
        clock->rotation = {0, 0, 1.6f*2};
        auto hourHand = std::make_unique<HourHand>();
        hourHand->position = clock->position + glm::vec3{0, 3, -2};
        hourHand->scale = {0.1f, 5, 0.1f};

        scene.objects.push_back(std::move(castleGate));
        scene.objects.push_back(std::move(castleWallLeft));
        scene.objects.push_back(std::move(castleWallRight));
        scene.objects.push_back(std::move(castleTowerBase));
        scene.objects.push_back(std::move(castleTowerTop));
        scene.objects.push_back(std::move(castleTowerBase1));
        scene.objects.push_back(std::move(castleTowerTop1));
        scene.objects.push_back(std::move(clock));
        scene.objects.push_back(std::move(hourHand));

        scene.camera = std::move(camera);
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
