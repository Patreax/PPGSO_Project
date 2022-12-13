#ifndef _PPGSO_SCENE_H
#define _PPGSO_SCENE_H

#include <memory>
#include <map>
#include <list>

#include "object.h"
#include "camera.h"
#include "spotLight.h"
#include "lightManager.h"

/*
 * Scene is an object that will aggregate all scene related data
 * Objects are stored in a list of objects
 * Keyboard and Mouse states are stored in a map and struct
 */
class Scene {
  public:
    /*!
     * Update all objects in the scene
     * @param time
     */
    void update(float time);

    /*!
     * Render all objects in the scene
     */
    void render();

    /*!
     * Pick objects using a ray
     * @param position - Position in the scene to pick object from
     * @param direction - Direction to pick objects from
     * @return Objects - Vector of pointers to intersected objects
     */
    std::vector<Object*> intersect(const glm::vec3 &position, const glm::vec3 &direction);

    // Camera object
    std::unique_ptr<Camera> camera;

    std::list< std::unique_ptr<Object>> inside;
    std::list< std::unique_ptr<Object>> outside;
    std::list< std::unique_ptr<Object>> side;
    std::list< std::unique_ptr<Object>> *current;


    // Keyboard state
    std::map< int, int > keyboard;

    // Lights, in this case using only simple directional diffuse lighting
    glm::vec3 lightDirection{-1.0f, -1.0f, -1.0f};

    std::list<std::unique_ptr<Light>> lights;
    std::unique_ptr<LightManager> lightManager;

    std::shared_ptr<ppgso::Shader> shadowMapShader;
    std::unique_ptr<ppgso::Shader> postProcessingShader;

    int sceneWidth = 1920;
    int sceneHeight = 1080;

    int shadowMapWidth = 1024;
    int shadowMapHeight = 1024;

    glm::mat4 lightProjection;

    unsigned int shadowMapFBO;
    unsigned int shadowMap;

    unsigned int postProcessingFBO;
    unsigned int postProcessingTexture;
    unsigned int RBO;
    unsigned int rectVao;


    // Store cursor state
    struct {
      double x, y;
      bool left, right;
    } cursor;
};

#endif // _PPGSO_SCENE_H
