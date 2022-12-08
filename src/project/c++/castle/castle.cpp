#include "castle.h"
#include "src/project/c++/scene.h"
#include "castleGate.h"
#include "castleWall.h"
#include "castleTowerBase.h"
#include "castleTowerTop.h"


Castle::Castle() {
}

void Castle::buildCastle(Scene &scene) {

    // Gate
    auto castleGate = std::make_unique<CastleGate>();
    castleGate->position = {0, -6, 0};

    // Wall
    auto castleWallLeftFront = std::make_unique<CastleWall>();
    castleWallLeftFront->position = castleGate->position + glm::vec3{30, -1.5f, 28};
    castleWallLeftFront->rotation = {0, 0, ppgso::PI / 2};

    auto castleWallRightFront = std::make_unique<CastleWall>();
    castleWallRightFront->position = castleGate->position + glm::vec3{-30, -1.5f, 28};
    castleWallRightFront->rotation = {0, 0, ppgso::PI / 2};

    auto castleWallLeftBack = std::make_unique<CastleWall>();
    castleWallLeftBack->position = castleGate->position + glm::vec3{30, -1.5f, 65};
    castleWallLeftBack->rotation = {0, 0, ppgso::PI / 2};

    auto castleWallRightBack = std::make_unique<CastleWall>();
    castleWallRightBack->position = castleGate->position + glm::vec3{-30, -1.5f, 65};
    castleWallRightBack->rotation = {0, 0, ppgso::PI / 2};

    auto castleWallBack = std::make_unique<CastleWall>();
    castleWallBack->position = castleGate->position + glm::vec3{0, -1.5f, 90};

    // towerBase
    auto castleTowerBaseLeftFront = std::make_unique<CastleTowerBase>();
    castleTowerBaseLeftFront->position = castleGate->position + glm::vec3{-29, -1, 0};

    auto castleTowerBaseRightFront = std::make_unique<CastleTowerBase>();
    castleTowerBaseRightFront->position = castleGate->position + glm::vec3{29, -1, 0};

    auto castleTowerBaseLeftBack = std::make_unique<CastleTowerBase>();
    castleTowerBaseLeftBack->position = castleGate->position + glm::vec3{-29, -1, 90};

    auto castleTowerBaseRightBack = std::make_unique<CastleTowerBase>();
    castleTowerBaseRightBack->position = castleGate->position + glm::vec3{29, -1, 90};

    // towerTop
    auto castleTowerTopLeftFront = std::make_unique<CastleTowerTop>();
    castleTowerTopLeftFront->position = castleTowerBaseLeftFront->position + glm::vec3{0, 13, 0};

    auto castleTowerTopRightFront = std::make_unique<CastleTowerTop>();
    castleTowerTopRightFront->position = castleTowerBaseRightFront->position + glm::vec3{0, 13, 0};

    auto castleTowerTopLeftBack = std::make_unique<CastleTowerTop>();
    castleTowerTopLeftBack->position = castleTowerBaseLeftBack->position + glm::vec3{0, 13, 0};

    auto castleTowerTopRightBack = std::make_unique<CastleTowerTop>();
    castleTowerTopRightBack->position = castleTowerBaseRightBack->position + glm::vec3{0, 13, 0};

    scene.objects.push_back(std::move(castleGate));
    scene.objects.push_back(std::move(castleWallLeftFront));
    scene.objects.push_back(std::move(castleWallRightFront));
    scene.objects.push_back(std::move(castleTowerBaseLeftFront));
    scene.objects.push_back(std::move(castleTowerTopLeftFront));
    scene.objects.push_back(std::move(castleTowerBaseRightFront));
    scene.objects.push_back(std::move(castleTowerTopRightFront));
    scene.objects.push_back(std::move(castleWallLeftBack));
    scene.objects.push_back(std::move(castleWallRightBack));
    scene.objects.push_back(std::move(castleTowerBaseLeftBack));
    scene.objects.push_back(std::move(castleTowerBaseRightBack));
    scene.objects.push_back(std::move(castleTowerTopLeftBack));
    scene.objects.push_back(std::move(castleTowerTopRightBack));
    scene.objects.push_back(std::move(castleWallBack));

}