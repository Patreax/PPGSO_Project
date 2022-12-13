#pragma once

#include <memory>
#include <list>
#include <map>

#include <glm/glm.hpp>
#include "objectMaterial.h"

#pragma once
#include <memory>
#include <list>
#include <map>
#include <ppgso/ppgso.h>


#include <glm/glm.hpp>
#include <unordered_map>
#include "keyframeAnimation.h"

class Scene;

class Object {
public:
    Object(std::string mesh, std::string texture);
    Object() = default;
    Object(const Object&) = default;
    Object(Object&&) = default;

    virtual bool update(Scene &scene, float dt);
    virtual bool update(Scene &scene, float dt, glm::mat4 parent);
    virtual bool update(Scene &scene, float dt, KeyframeAnimation &anim);

    virtual void render(Scene &scene);

    // Object properties
    glm::vec3 position{0,0,0};
    glm::vec3 rotation{0,0,0};
    glm::vec3 scale{1,1,1};
    glm::mat4 modelMatrix{1};

    static std::unordered_map<std::string, ppgso::Mesh *> meshes;
    static std::unordered_map<std::string, ppgso::Texture *> textures;

    /*
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Texture> texture;
     */

    ppgso::Mesh *mesh;
    ppgso::Texture *texture;
    static std::unique_ptr<ppgso::Shader> shader;

    std::vector<std::unique_ptr<Object>> children;
    std::unique_ptr<ObjectMaterial> objectMaterial;


    void generateModelMatrix();
    void generateModelMatrix(glm::mat4 parent);
    void renderShadows(Scene &scene, std::shared_ptr<ppgso::Shader> shader);

};
class Scene;

/*
class Object {
public:
    Object() = default;

    Object(const Object &) = default;

    Object(Object &&) = default;

    virtual ~Object() {};

    virtual bool update(Scene &scene, float dt) = 0;

    virtual void render(Scene &scene) = 0;

    void renderShadows(Scene &scene, std::shared_ptr<ppgso::Shader> shader);


    // Object properties
    glm::vec3 position{0, 0, 0};
    glm::vec3 rotation{0, 0, 0};
    glm::vec3 scale{1, 1, 1};
    glm::mat4 modelMatrix{1};

    std::unique_ptr<ObjectMaterial> objectMaterial;

protected:
    void generateModelMatrix();
};
*/
