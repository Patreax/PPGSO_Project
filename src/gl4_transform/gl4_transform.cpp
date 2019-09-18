// Example gl4_transform
// - This example demonstrates basic transformations
// - Notice that the glm library uses column major order when declaring matrices
// - Example combines multiple transformation using multiplication
// - Press SPACE to see each transformation

#include <iostream>

#include <ppgso/ppgso.h>

#include <shaders/texture_vert_glsl.h>
#include <shaders/texture_frag_glsl.h>

const unsigned int SIZE = 512;

/*!
 * Custom window for demonstrating transformations
 */
class TransformWindow : public ppgso::Window {
private:
  // Set up needed resources
  ppgso::Shader program = {texture_vert_glsl, texture_frag_glsl};
  ppgso::Texture texture = {ppgso::image::loadBMP("lena.bmp")};
  ppgso::Mesh quad = {"quad.obj"};

  // Mode switch
  enum class Mode {
    IDENTITY,
    SCALE,
    SQUASH,
    ROTATE,
    TRANSLATE,
    ROTATE_TOP_RIGHT,
    ROTATE_TOP_LEFT,
    END,
  } mode = Mode::SCALE;

  /*!
   * Generate transformation matrix
   * @param time Time to use as parameter or matrix generation
   * @return Model transformation matrix
   */
  glm::mat4 getModelTransformationMatrix(float time) {
    // Create transformation matrix
    // NOTE: glm matrices are declared column major !
    switch (mode) {
      case Mode::IDENTITY:
        return glm::mat4({
          1.0, 0.0, 0.0, 0.0,
          0.0, 1.0, 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0,
          0.0, 0.0, 0.0, 1.0,
        });

      case Mode::SCALE:
        return glm::mat4({
          sin(time), 0.0, 0.0, 0.0,
          0.0, sin(time), 0.0, 0.0,
          0.0, 0.0, sin(time), 0.0,
          0.0, 0.0, 0.0, 1.0,
        });

      case Mode::SQUASH:
        return glm::mat4({
          sin(time), 0.0, 0.0, 0.0,
          0.0, cos(time), 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0,
          0.0, 0.0, 0.0, 1.0,
        });

      case Mode::ROTATE:
        return glm::mat4({
          cos(time), sin(time), 0.0, 0.0,
          -sin(time), cos(time), 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0,
          0.0, 0.0, 0.0, 1.0,
        });

      case Mode::TRANSLATE:
        return glm::mat4({
          1.0, 0.0, 0.0, 0.0,
          0.0, 1.0, 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0,
          sin(time) / 2.0, cos(time) / 2.0, 0.0, 1.0,
        });

      case Mode::ROTATE_TOP_RIGHT:
        return glm::mat4({ // Move back
          1.0, 0.0, 0.0, 0.0,
          0.0, 1.0, 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0,
          1.0, 1.0, 0.0, 1.0,
        }) * glm::mat4({ // Rotate
          cos(time), sin(time), 0.0, 0.0,
          -sin(time), cos(time), 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0,
          0.0, 0.0, 0.0, 1.0,
        }) * glm::mat4({ // Move to origin
          1.0, 0.0, 0.0, 0.0,
          0.0, 1.0, 0.0, 0.0,
          0.0, 0.0, 1.0, 0.0,
          -1.0, -1.0, 0.0, 1.0,
        });

      case Mode::ROTATE_TOP_LEFT:
        return translate(glm::mat4{1.0f}, glm::vec3{-1, 1, 0})
               * rotate(glm::mat4{1.0f}, time, glm::vec3{0, 0, 1})
               * glm::translate(glm::mat4{1.0f}, -glm::vec3{-1, 1, 0});

      default:
        break;
    }
    return glm::mat4{1.0f};
  }

public:
  /*!
   * Create new custom window
   */
  TransformWindow() : Window{"gl4_transform", SIZE, SIZE} {
    // Set program input for texture uniform
    program.setUniform("Texture", texture);
    // Set Matrices to identity so there are no projections/transformations applied in the vertex shader
    program.setUniform("ViewMatrix", glm::mat4{1.0f});
    program.setUniform("ProjectionMatrix", glm::mat4{1.0f});
  }

  /*!
   * Handles pressed key when the window is focused
   * @param key Key code of the key being pressed/released
   * @param scanCode Scan code of the key being pressed/released
   * @param action Action indicating the key state change
   * @param mods Additional modifiers to consider
   */
  void onKey(int key, int scanCode, int action, int mods) override {
    // When SPACE is pressed advance mode to the next state
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
      int next_mode = ((int)mode+1) % (int)Mode::END;
      mode = Mode(next_mode % 8);
    }
  };

  /*!
   * Window update implementation that will be called automatically from pollEvents
   */
  void onIdle() override {
    // Set gray background
    glClearColor(.5f, .5f, .5f, 0);

    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto time = glfwGetTime();

    // Generate and set the transformation matrix
    program.setUniform("ModelMatrix", getModelTransformationMatrix((float)time));

    // Render geometry
    quad.render();
  }
};

int main() {
  // Create our window
  TransformWindow window;

  // Main execution loop
  while (window.pollEvents()) {}

  return EXIT_SUCCESS;
}
