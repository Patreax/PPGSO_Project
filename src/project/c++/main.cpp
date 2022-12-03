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
#include "rock.h"
#include "ground.h"
#include "random"
#include "tree.h"
#include "water.h"

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
    void addGround(int x1,int x2,int z1,int z2,int y,glm::vec3 rotation){
        for(int i = x1; i < x2; i += 10){
            for(int j = z1; j < z2; j += 10){
                auto ground = std::make_unique<Ground>();
                ground->scale = {2,2,2,};
                ground->rotation = rotation;
                ground->position = {i,y,j};
                scene.objects.push_back(std::move(ground));
            }
        }
    }

    void addWater(int x1,int x2,int z1,int z2,int y){
        for(int i = x1; i < x2; i += 10){
            for(int j = z1; j < z2; j += 10){
                auto water = std::make_unique<Water>();
                water->scale = {2,2,2,};
                water->rotation = glm::vec3 {0,0,0};
                water->position = {i,y,j};
                scene.objects.push_front(std::move(water));
            }
        }
    }

    void initScene() {
        scene.objects.clear();

        // Create a camera
        auto camera = std::make_unique<Camera>(60.0f, 1.0f, 0.1f, 200.0f);
        camera->position.z = -55.0f;

        // Gate
        auto castleGate = std::make_unique<CastleGate>();
        castleGate->position = {0, -6, 0};

        // Wall
        auto castleWallLeftFront = std::make_unique<CastleWall>();
        castleWallLeftFront->position = castleGate->position + glm::vec3{25, 0, 25};
        castleWallLeftFront->rotation = {0, 0, 1.6f};

        auto castleWallRightFront = std::make_unique<CastleWall>();
        castleWallRightFront->position = castleGate->position + glm::vec3{-25, 0, 25};
        castleWallRightFront->rotation = {0, 0, 1.6f};

        // Rocks

        for(int i = 1; i < 20; i++){
            auto rock = std::make_unique<Rock>();
            rock->position = {-(double)rand()/(double)RAND_MAX * 44.0f - 35.0f,-13.5,(float)rand()/(double)RAND_MAX * 120.0f -20.0f};

            scene.objects.push_back(std::move(rock));
        }

        // Trees
        for(int i = 1; i < 20; i++){
            auto tree = std::make_unique<Tree>();
            tree->position = {-(double)rand()/(double)RAND_MAX * 44.0f -35.0f,-13.5,(float)rand()/(double)RAND_MAX * 120.0f -20.0f};

            scene.objects.push_back(std::move(tree));
        }

        //Ground
        addGround(-100, 100, -20, 150, -16, glm::vec3{0,0,0});
        addGround(-100, 100, -80, -40, -16, glm::vec3{0,0,0});
        addGround(-100, 100, -28.68, -20, -19.96, glm::vec3{rad(-45),0,0});
        addGround(-100, 100, -42, -35, -19.96, glm::vec3{rad(45),0,0});
        addGround(-100, 100, -35, -30, -23, glm::vec3{0,0,0});

        // Water
        addWater(-100, 100, -40, -25, -18);

        // towerBase
        auto castleTowerBaseLeftFront = std::make_unique<CastleTowerBase>();
        castleTowerBaseLeftFront->position = castleGate->position + glm::vec3{-30, -1, 0};
        // towerTop
        auto castleTowerTopLeftFront = std::make_unique<CastleTowerTop>();
        castleTowerTopLeftFront->position = castleTowerBaseLeftFront->position + glm::vec3{0, 13, 0};

        auto castleTowerBaseRightFront = std::make_unique<CastleTowerBase>();
        castleTowerBaseRightFront->position = castleGate->position + glm::vec3{30, -1, 0};
        auto castleTowerTopRightFront = std::make_unique<CastleTowerTop>();
        castleTowerTopRightFront->position = castleTowerBaseRightFront->position + glm::vec3{0, 13, 0};

        auto castleWallLeftBack = std::make_unique<CastleWall>();
        castleWallLeftBack->position = castleGate->position + glm::vec3{25, 0, 60};
        castleWallLeftBack->rotation = {0, 0, 1.6f};

        // clock
        auto clock = std::make_unique<Clock>();
        clock->position = {0, 0, -15};
        clock->scale = {0.1f, 0.1f, 0.1f};
        clock->rotation = {0, 0, 1.6f*2};
        auto hourHand = std::make_unique<HourHand>();
        hourHand->position = clock->position + glm::vec3{0, 3, -2};
        hourHand->scale = {0.1f, 5, 0.1f};

        // Castle
        scene.objects.push_back(std::move(castleGate));
        scene.objects.push_back(std::move(castleWallLeftFront));
        scene.objects.push_back(std::move(castleWallRightFront));
        scene.objects.push_back(std::move(castleTowerBaseLeftFront));
        scene.objects.push_back(std::move(castleTowerTopLeftFront));
        scene.objects.push_back(std::move(castleTowerBaseRightFront));
        scene.objects.push_back(std::move(castleTowerTopRightFront));
        scene.objects.push_back(std::move(castleWallLeftBack));

        // Clock
        scene.objects.push_back(std::move(clock));
        scene.objects.push_back(std::move(hourHand));

        scene.camera = std::move(camera);
    }

public:

    float rad(float degree){
        return degree * (ppgso::PI / 180);
    }

    /*!
     * Construct custom game window
     */
    SceneWindow() : Window{"demo", WIDTH, HEIGHT} {
        //hideCursor();
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


        // Initialize OpenGL state
        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Enable polygon culling
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        initScene();
        //Center cursor
        glfwSetCursorPos(window ,1920 / 2, 1080 / 2);
        scene.camera->firstMouse = true;
        onCursorPos(1920 / 2, 1080 / 2);
        scene.lightDirection = {-1,200,-25};

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
