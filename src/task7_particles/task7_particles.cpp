// Task 7 - Dynamically generate objects in a 3D scene
//        - Implement a particle system where particles have position and speed
//        - Any object can be a generator and can add objects to the scene
//        - Create dynamic effect such as fireworks, rain etc.
//        - Encapsulate camera in a class

#include <iostream>
#include <vector>
#include <map>
#include <list>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include <ppgso/ppgso.h>

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

const unsigned int SIZE = 512;

class Camera {
public:
    // TODO: Add parameters
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    glm::vec3 position = {10, 5, 15};

    /// Representaiton of
    /// \param fov - Field of view (in degrees)
    /// \param ratio - Viewport ratio (width/height)
    /// \param near - Distance of the near clipping plane
    /// \param far - Distance of the far clipping plane
    Camera(float fov = 45.0f, float ratio = 1.0f, float near = 0.1f, float far = 10.0f) {
        // TODO: Initialize perspective projection (hint: glm::perspective)
        projectionMatrix = glm::perspective(fov, ratio, near, far);
    }

    /// Recalculate viewMatrix from position, rotation and scale
    void update() {
        // TODO: Update viewMatrix (hint: glm::lookAt)
        viewMatrix = glm::lookAt(this->position, {0, 0, 0}, {0, 1, 0});
    }
};

/// Abstract renderable object interface
class Renderable; // Forward declaration for Scene
using Scene = std::list<std::unique_ptr<Renderable>>; // Type alias
glm::vec3 sunPosition = {0, 5, 5};

class Renderable {
public:
    // Virtual destructor is needed for abstract interfaces
    virtual ~Renderable() = default;

    /// Render the object
    /// \param camera - Camera to use for rendering
    virtual void render(const Camera &camera) = 0;

    /// Update the object. Useful for specifing animation and behaviour.
    /// \param dTime - Time delta
    /// \param scene - Scene reference
    /// \return - Return true to keep object in scene
    virtual bool update(float dTime, Scene &scene) = 0;
};

class Sun final : public Renderable{
    // Static resources shared between all particles
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;

    // TODO: add more parameters as needed
public:
    glm::mat4 modelMatrix{1.0f};

    glm::vec3 position = {0, 0, 0};
    glm::vec3 rotation = {0, 0, 0};
    glm::vec3 scale = {0.05f, 0.05f, 0.05f};
    glm::vec3 initialSpeed = {0, -1, 0};
    glm::vec3 color = {0, 128, 255};

    float timeToLive = 3.0f;
    double time = 0;
    float radius = 5;

    /// Construct a new Particle
    /// \param p - Initial position
    /// \param s - Initial speed
    /// \param c - Color of particle
    Sun(glm::vec3 p, glm::vec3 s, glm::vec3 c) {
        // First particle will initialize resources
        if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
        if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");

        this->scale = {.1f, .1f, .1f};
        this->color = c;
        this->position = p;
    }

    bool update(float dTime, Scene &scene) override {
        // TODO: Animate position using speed and dTime.
        // - Return true to keep the object alive
        // - Returning false removes the object from the scene
        // - hint: you can add more particles to the scene here also

        time += dTime;

        this->position = {cos(time) * radius,1, sin(time) * radius};
        sunPosition = this->position;
        modelMatrix = glm::translate(glm::mat4{1.0f}, this->position);

        return true;
    }

    void render(const Camera &camera) override {
        // TODO: Render the object
        // - Use the shader
        // - Setup all needed shader inputs
        // - hint: use OverallColor in the color_vert_glsl shader for color
        // - Render the mesh

        shader->use();
        shader->setUniform("ProjectionMatrix", camera.projectionMatrix);
        shader->setUniform("ViewMatrix", camera.viewMatrix);
        shader->setUniform("ModelMatrix", modelMatrix);
        shader->setUniform("OverallColor", color);

        mesh->render();
    }
};

class Moon final : public Renderable{
    // Static resources shared between all particles
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;

    // TODO: add more parameters as needed
public:
    glm::mat4 modelMatrix{1.0f};

    glm::vec3 position = {0, 0, 0};
    glm::vec3 rotation = {0, 0, 0};
    glm::vec3 scale = {0.05f, 0.05f, 0.05f};
    glm::vec3 initialSpeed = {0, -1, 0};
    glm::vec3 color = {0, 128, 255};

    float timeToLive = 3.0f;
    double time = 0;
    float radius = 5;
    float offset = 60;

    /// Construct a new Particle
    /// \param p - Initial position
    /// \param s - Initial speed
    /// \param c - Color of particle
    Moon(glm::vec3 p, glm::vec3 s, glm::vec3 c) {
        // First particle will initialize resources
        if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
        if (!mesh) mesh = std::make_unique<ppgso::Mesh>("sphere.obj");

        this->scale = {.1f, .1f, .1f};
        this->color = c;
        this->position = p;
    }

    bool update(float dTime, Scene &scene) override {
        // TODO: Animate position using speed and dTime.
        // - Return true to keep the object alive
        // - Returning false removes the object from the scene
        // - hint: you can add more particles to the scene here also

        time += dTime;

        this->position = {cos(time + offset) * radius ,1, sin(time + offset) * radius};
        modelMatrix = glm::translate(glm::mat4{1.0f}, this->position);

        return true;
    }

    void render(const Camera &camera) override {
        // TODO: Render the object
        // - Use the shader
        // - Setup all needed shader inputs
        // - hint: use OverallColor in the color_vert_glsl shader for color
        // - Render the mesh

        shader->use();
        shader->setUniform("ProjectionMatrix", camera.projectionMatrix);
        shader->setUniform("ViewMatrix", camera.viewMatrix);
        shader->setUniform("ModelMatrix", modelMatrix);
        shader->setUniform("OverallColor", color);

        mesh->render();
    }
};

/// Basic particle that will render a sphere
/// TODO: Implement Renderable particle
class Particle final : public Renderable {
    // Static resources shared between all particles
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;

    // TODO: add more parameters as needed
public:
    glm::mat4 modelMatrix{1.0f};

    glm::vec3 position = {0, 0, 0};
    glm::vec3 rotation = {0, 0, 0};
    glm::vec3 scale = {0.05f, 0.05f, 0.05f};
    glm::vec3 initialSpeed = {0, -1, 0};
    glm::vec3 color = {0, 128, 255};
    glm::vec3 direction = {0,1,0};

    float timeToLive = 3.0f;
    float speed = 50;

    /// Construct a new Particle
    /// \param p - Initial position
    /// \param s - Initial speed
    /// \param c - Color of particle
    Particle(glm::vec3 p, glm::vec3 s, glm::vec3 c) {
        // First particle will initialize resources
        if (!shader) shader = std::make_unique<ppgso::Shader>(color_vert_glsl, color_frag_glsl);
        if (!mesh) mesh = std::make_unique<ppgso::Mesh>("cube.obj");


        this->scale = {.05f, .05f, .5f};
        this->color = c;
//        this->rotation = {0,0,rand()%360};
        this->position = p;
        this->direction = {((double) rand() / (RAND_MAX)) / speed, ((double) rand() / (RAND_MAX)) / speed, ((double) rand() / (RAND_MAX)) / speed};
    }

    bool update(float dTime, Scene &scene) override {
        // TODO: Animate position using speed and dTime.
        // - Return true to keep the object alive
        // - Returning false removes the object from the scene
        // - hint: you can add more particles to the scene here also

//        glm::vec3 direction = {0,-0.02f,0};
//        this->position = this->position + direction;
//
//
//        double x = ((double) rand() / (RAND_MAX));
//        std::cout << x;

        this->position = this->position + this->direction;

        modelMatrix = glm::translate(glm::mat4{1.0f}, this->position) * glm::scale(glm::mat4{1.0f}, this->scale);


        this->timeToLive -= dTime;
        if (this->timeToLive < 0) {
//            std::cout << "Time to live exceeded\n";
            return false;
        }

        return true;
    }

    void render(const Camera &camera) override {
        // TODO: Render the object
        // - Use the shader
        // - Setup all needed shader inputs
        // - hint: use OverallColor in the color_vert_glsl shader for color
        // - Render the mesh

        shader->use();
        shader->setUniform("ProjectionMatrix", camera.projectionMatrix);
        shader->setUniform("ViewMatrix", camera.viewMatrix);
        shader->setUniform("ModelMatrix", modelMatrix);
        shader->setUniform("OverallColor", color);

        mesh->render();
    }
};

// Static resources need to be instantiated outside of the class as they are globals
std::unique_ptr<ppgso::Mesh> Particle::mesh;
std::unique_ptr<ppgso::Shader> Particle::shader;

std::unique_ptr<ppgso::Mesh> Sun::mesh;
std::unique_ptr<ppgso::Shader> Sun::shader;

std::unique_ptr<ppgso::Mesh> Moon::mesh;
std::unique_ptr<ppgso::Shader> Moon::shader;

class ParticleWindow : public ppgso::Window {
private:
    // Scene of objects
    Scene scene;

    // Create camera
    Camera camera = {120.0f, (float) width / (float) height, 1.0f, 400.0f};

    // Store keyboard state
    std::map<int, int> keys;
public:

//    glm::vec3 sunPosition = {0, 5, 5};

    ParticleWindow() : Window{"task7_particles", SIZE, SIZE} {

        // Initialize OpenGL state
        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        glm::vec3 initialSpeed = {0, -.1, 0};
        glm::vec3 color = {1, 1, 0};
        scene.push_back(std::make_unique<Sun>(sunPosition, initialSpeed, color));

        glm::vec3 moonPosition = {sunPosition.x, sunPosition.y, sunPosition.z * (-1)};
        glm::vec3 moonColor = {1, 1, 1};
        scene.push_back(std::make_unique<Moon>(moonPosition, initialSpeed, moonColor));
    }

    void onKey(int key, int scanCode, int action, int mods) override {
        // Collect key state in a map
        keys[key] = action;
        if (keys[GLFW_KEY_SPACE]) {
            // TODO: Add renderable object to the scene

            const int radius = 2;

//            glm::vec3 position = {0, 0, 0};

            glm::vec3 position = {sunPosition.x + rand()%radius, sunPosition.y, sunPosition.z + rand()%radius};
            glm::vec3 initialSpeed = {0, -.1, 0};
            glm::vec3 color = {1, .5, 0};
            scene.push_back(std::make_unique<Particle>(position, initialSpeed, color));
        }
    }

    void onIdle() override {
        // Track time
        static auto time = (float) glfwGetTime();
        // Compute time delta
        float dTime = (float) glfwGetTime() - time;
        time = (float) glfwGetTime();

        // Set gray background
        glClearColor(.1f, .1f, .1f, 1.0f);

        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.update();

        // Update all objects in scene
        // Because we need to delete while iterating this is implemented using c++ iterators
        // In most languages mutating the container during iteration is undefined behaviour
        auto i = std::begin(scene);
        while (i != std::end(scene)) {
            // Update object and remove from list if needed
            auto obj = i->get();
            if (!obj->update(dTime, scene)) {
                i = scene.erase(i);
            } else {
                ++i;
            }
        }

        // Render every object in scene
        for (auto &object: scene) {
            object->render(camera);
        }
    }
};

int main() {
    // Create new window
    auto window = ParticleWindow{};

    // Main execution loop
    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}
