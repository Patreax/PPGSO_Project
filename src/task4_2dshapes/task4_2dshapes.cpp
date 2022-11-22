// Task 5 - Draw a 2D shape using polygons and animate it
//        - Encapsulate the shape using a class
//        - Use color_vert/frag shader to display the polygon
//        - Animate the object position, rotation and scale.

#include <iostream>
#include <vector>
#include <math.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <ppgso/ppgso.h>

#include <shaders/color_vert_glsl.h>
#include <shaders/color_frag_glsl.h>

const unsigned int SIZE = 512;

// Object to represent 2D OpenGL shape
class Shape {
private:
  // 2D vectors define points/vertices of the shape
  // TODO: Define your shape points     // vrcholy
  std::vector<glm::vec3> vetrices = {
//          {-.3, -.3, 0},
//          {-.3, .3, 0},
//          {.3, .3, 0},
//          {.3, -.3, 0}

          {-.5,.5, 0},
          {.5,.5,0},
          {1,0,0},
          {.5,-.5,0},
          {.2,-.5,0},
          {.3,-.5,0},
          {.1,-.5,0},
          {-.2,-.5,0},
          {-.1,-.5,0},
          {-.3,-.5,0},
          {-.5,-.5,0},
          {0,.5,0},
          {.5, 1, 0}

  };

  // Structure representing a triangular face, usually indexes into vertices
  struct Face {                         // definovana trojuholnikmi
    // TODO: Define your face structure
    int a, b, c;

  };

  // Indices define triangles that index into vertices
  // TODO: Define your mesh indices     // samotny objekt
//  Face face1 = *new Face();

  std::vector<Face> mesh = {
          {0,1,3},
          {0,10,3},
          {1,2,3},
          {1,11,12}
  };

  // Program to associate with the object
  ppgso::Shader program = {color_vert_glsl, color_frag_glsl};

  // These will hold the data and object buffers
  GLuint vao, vbo, cbo, ibo;
  glm::mat4 modelMatrix{1.0f};      // transformacia objektu
public:
  // Public attributes that define position, color ..
  glm::vec3 position{-1,0,0};
  glm::vec3 rotation{0,0,0};
  glm::vec3 scale{1,1,1};
  glm::vec3 color{1,0,0};

  // Initialize object data buffers
  Shape() {
    // Copy data to OpenGL
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Copy positions to gpu
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vetrices.size() * sizeof(glm::vec3), vetrices.data(), GL_STATIC_DRAW);

    // Set vertex program inputs
    auto position_attrib = program.getAttribLocation("Position");
    glEnableVertexAttribArray(position_attrib);
    glVertexAttribPointer(position_attrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // Copy mesh indices to gpu
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.size() * sizeof(Face), mesh.data(), GL_STATIC_DRAW);

    // Set projection matrices to identity
    program.setUniform("ProjectionMatrix", glm::mat4{1.0f});
    program.setUniform("ViewMatrix", glm::mat4{1.0f});
  };
  // Clean up
  ~Shape() {
    // Delete data from OpenGL
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &cbo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
  }

  // Set the object transformation matrix
  void update() {
    // TODO: Compute transformation by scaling, rotating and then translating the shape
//    modelMatrix = glm::translate(glm::mat4{1.0f}, position) * glm::scale(glm::mat4{1.0f}, scale) * glm::rotate(glm::mat4{1.0f}, rotation.z, {0,0,1});
//    modelMatrix = glm::scale(glm::mat4{1.0f}, scale);
    modelMatrix = glm::rotate(glm::mat4{1.0f}, rotation.z, {0,0,0.2}) * glm::translate(glm::mat4{1.0f}, position) * glm::scale(glm::mat4{1.0f}, {0.1,0.1, 0.1});
  }

  // Draw polygons
  void render(){
    // Update transformation and color uniforms in the shader
    program.use();
    program.setUniform("OverallColor", color);
    program.setUniform("ModelMatrix", modelMatrix);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, (GLsizei) mesh.size() * 3, GL_UNSIGNED_INT, 0);
  };
};

class ShapeWindow : public ppgso::Window {
private:
  Shape shape1, shape2, shape3;
public:
  ShapeWindow() : Window{"task4_2dshapes", SIZE, SIZE} {
    shape1.color = {1,0,0};
    shape2.color = {0,1,0};
    shape3.color = {0,0,1};
    shape2.position = {-0.9, 0 ,0};
  }

  int control1 = 1;
  int control2 = 1;

  float direction1 = 0.0001f;
  float direction2 = 0.0001f;

  void onIdle() {
    // Set gray background
    glClearColor(.1f,.1f,.1f,1.0f);
    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Move and Render shape\    // Get time for animation
    auto t = (float) glfwGetTime();
    float currentXPosition1 = shape1.position.x;
    float currentXPosition2 = shape2.position.x;

    if(int(shape1.position.x) == -1){
        direction1 = 0.0001f;
    }
    if(int(shape1.position.x) == 1){
        direction1 = -0.0001f;
    }
    if(int(shape2.position.x) == -1){
      direction2 = 0.0001f;
    }
    if(int(shape2.position.x) == 1){
      direction2 = -0.0001f;
    }


    // TODO: manipulate shape1 and shape2 position to rotate clockwise
    shape1.position = {currentXPosition1 + direction1, abs(sin(t) / 5) * control1, 0};
    shape2.position = {currentXPosition2 + direction2, abs(cos(t) / 5) * control2, 0};

    if(shape2.position.y <= 0.0001 && shape1.position.x < shape2.position.x){
        direction2 = 0;
        control1 = 1;
        control2 = 0;
        direction1 = 0.0001f;
    }
    if(shape1.position.y <= 0.0001 && shape1.position.x > shape2.position.x){
        direction1 = 0;
        control1 = 0;
        control2 = 1;
        direction2 = 0.0001f;
    }





    // Manipulate rotation of the shape
    shape3.rotation.z = t*2.0f;
//    shape2.rotation = -shape1.rotation;

    // Manipulate shape size
//    shape1.scale = {sin(t),sin(t), 1};
//    shape2.scale = -shape1.scale;

    // Update and render each shape
    shape1.update();
    shape2.update();
    shape3.update();

    shape1.render();
    shape2.render();
    shape3.render();
  }
};

int main() {
  // Create our window
  auto window = ShapeWindow{};

  // Main execution loop
  while (window.pollEvents()) {}

  return EXIT_SUCCESS;
}
