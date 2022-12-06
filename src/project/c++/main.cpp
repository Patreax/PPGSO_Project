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
#include "boat.h"
#include "riverGenerator.h"

const unsigned int SIZE = 512;

const unsigned int WIDTH = 1920;
const unsigned int HEIGHT = 1080;

class SceneWindow : public ppgso::Window {
private:
    Scene scene;
    //float elapsed = 0;

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
        scene.camera = std::move(camera);

        // Rocks
        for(int i = 1; i < 20; i++){
            auto rock = std::make_unique<Rock>();
            rock->position = {-(double)rand()/(double)RAND_MAX * 44.0f - 35.0f,-13.5,(float)rand()/(double)RAND_MAX * 120.0f -20.0f};

            scene.objects.push_back(std::move(rock));
        }
        for(int i = 1; i < 20; i++){
            auto rock = std::make_unique<Rock>();
            rock->position = {(double)rand()/(double)RAND_MAX * 200.0f - 100.0f,-13.5,(float)rand()/(double)RAND_MAX * 30.0f -80.0f};

            scene.objects.push_back(std::move(rock));
        }

        // Trees
        for(int i = 1; i < 20; i++){
            auto tree = std::make_unique<Tree>();
            tree->position = {-(double)rand()/(double)RAND_MAX * 44.0f -35.0f,-13.5,(float)rand()/(double)RAND_MAX * 120.0f -20.0f};

            scene.objects.push_back(std::move(tree));
        }
        for(int i = 1; i < 20; i++){
            auto tree = std::make_unique<Tree>();
            tree->position = {(double)rand()/(double)RAND_MAX * 200.0f - 100.0f,-13.5,(float)rand()/(double)RAND_MAX * 30.0f -80.0f};

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

        // River Generator
        auto riverGenerator = std::make_unique<RiverGenerator>();
        scene.objects.push_back(std::move(riverGenerator));

        // Gate
        auto castleGate = std::make_unique<CastleGate>();
        castleGate->position = {0, -6, -17};
        castleGate->rotation.z = rad(180);

        // towerBases
        auto castleTowerBaseLeftFront = std::make_unique<CastleTowerBase>();
        castleTowerBaseLeftFront->position = castleGate->position + glm::vec3{-28, -1, 0};

        auto castleTowerBaseRightFront = std::make_unique<CastleTowerBase>();
        castleTowerBaseRightFront->position = castleGate->position + glm::vec3{28, -1, 0};

        // towerTops
        auto castleTowerTopLeftFront = std::make_unique<CastleTowerTop>();
        castleTowerTopLeftFront->position = castleTowerBaseLeftFront->position + glm::vec3{0, 13, 0};
        scene.objects.push_back(std::move(castleTowerTopLeftFront));

        auto castleTowerTopRightFront = std::make_unique<CastleTowerTop>();
        castleTowerTopRightFront->position = castleTowerBaseRightFront->position + glm::vec3{0, 13, 0};
        scene.objects.push_back(std::move(castleTowerTopRightFront));

        // Wall MAGIC number for walls is 21 from the center
        auto castleWallLeftFront = std::make_unique<CastleWall>();
        castleWallLeftFront->position = castleTowerBaseLeftFront->position + glm::vec3{0, 0, 28};
        castleWallLeftFront->rotation = {0, 0, rad(90)};

        auto castleWallRightFront = std::make_unique<CastleWall>();
        castleWallRightFront->position = castleTowerBaseRightFront->position + glm::vec3{0, 0, 28};
        castleWallRightFront->rotation = {0, 0, rad(90)};

        auto castleWallLeftBack = std::make_unique<CastleWall>();
        castleWallLeftBack->position = castleWallLeftFront->position + glm::vec3{0, 0, 42};
        castleWallLeftBack->rotation = {0, 0, rad(90)};

        auto castleWallRightBack = std::make_unique<CastleWall>();
        castleWallRightBack->position = castleWallRightFront->position + glm::vec3{0, 0, 42};
        castleWallRightBack->rotation = {0, 0, rad(90)};

        // Back towerBases
        auto castleTowerBaseLeftBack = std::make_unique<CastleTowerBase>();
        castleTowerBaseLeftBack->position = castleWallLeftBack->position + glm::vec3{0, -1, 28};

        auto castleTowerBaseRightBack = std::make_unique<CastleTowerBase>();
        castleTowerBaseRightBack->position = castleWallRightBack->position + glm::vec3{0, -1, 28};

        // Back towerTops
        auto castleTowerTopLeftBack = std::make_unique<CastleTowerTop>();
        castleTowerTopLeftBack->position = castleTowerBaseLeftBack->position + glm::vec3{0, 13, 0};
        scene.objects.push_back(std::move(castleTowerTopLeftBack));

        auto castleTowerTopRightBack = std::make_unique<CastleTowerTop>();
        castleTowerTopRightBack->position = castleTowerBaseRightBack->position + glm::vec3{0, 13, 0};
        scene.objects.push_back(std::move(castleTowerTopRightBack));

        // Back wall
        auto castleWallBack = std::make_unique<CastleWall>();
        castleWallBack->position = castleTowerBaseRightBack->position + glm::vec3{-28, 1, 0};
        castleWallBack->rotation = {0, 0, 0};

        // Moving castle parts
        scene.objects.push_back(std::move(castleGate));

        scene.objects.push_back(std::move(castleTowerBaseLeftFront));
        scene.objects.push_back(std::move(castleTowerBaseRightFront));
        scene.objects.push_back(std::move(castleTowerBaseLeftBack));
        scene.objects.push_back(std::move(castleTowerBaseRightBack));

        scene.objects.push_back(std::move(castleWallLeftFront));
        scene.objects.push_back(std::move(castleWallRightFront));
        scene.objects.push_back(std::move(castleWallLeftBack));
        scene.objects.push_back(std::move(castleWallRightBack));
        scene.objects.push_back(std::move(castleWallBack));

        // clock
        auto clock = std::make_unique<Clock>();
        clock->position = {0, 0, -20};
        clock->scale = {0.1f, 0.1f, 0.1f};
        clock->rotation = {0, 0, rad(180)};
        auto hourHand = std::make_unique<HourHand>();
        hourHand->position = clock->position + glm::vec3{0, 3, 2};
        hourHand->scale = {0.1f, 5, 0.1f};

        // Clock
        scene.objects.push_back(std::move(clock));
        scene.objects.push_back(std::move(hourHand));
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
        //elapsed += dt;
        time = (float) glfwGetTime();
        //std::cout << elapsed << "\n";

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
