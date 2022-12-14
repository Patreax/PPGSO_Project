# This CMake script is designed for CLion IDE and QTCreator projects on Windows
# It should find bundled binary dependencies automatically when using MinGW compiler
# On Linux and Mac the dependencies (glm, glew, glfw) need to be installed manually

cmake_minimum_required(VERSION 3.1)
project(ppgso CXX)

#
# CONFIGURATION
#

# Basic CMake settings
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/_install)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/data)

# Use add_resources function to convert .glsl to a .cpp files which will be compiled into a separate static library
include(add_resources)

#
# DEPENDENCIES
#

# Set up external dependencies for Windows users
if (MINGW)
  set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/include/")
  set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/lib/mingw")
elseif (MSVC)
  set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/dependencies/include/")
  if(MSVC_VERSION == 1500)
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/lib/vc2015")
  elseif(MSVC_VERSION >= 1900)
    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/dependencies/lib/vc2019")
  endif()
  set(USE_STRICT_COMPILE_WARNINGS OFF CACHE BOOL "" FORCE)
endif ()

# Warnings for Debug mode
option(USE_STRICT_COMPILE_WARNINGS "Use strict compilation warnings in debug mode." ON)
# These compile flags should apply for GCC and Clang compilers
set(STRICT_COMPILE_FLAGS "-Wpedantic -Wall -Wno-c++98-compat -Wextra -Wno-sign-conversion -Wno-unused-parameter")
if (USE_STRICT_COMPILE_WARNINGS)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${STRICT_COMPILE_FLAGS}")
endif ()

# Find required packages
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)

# Optional packages
find_package(OpenMP)
if(OPENMP_FOUND)
  list(APPEND CMAKE_CXX_FLAGS ${OpenMP_CXX_FLAGS})
endif()

# Set default installation destination
if (NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "../_install")
endif ()

#
# Shaders / Materials
#

set(PPGSO_SHADER_SRC
        shader/color_vert.glsl shader/color_frag.glsl
        shader/convolution_vert.glsl shader/convolution_frag.glsl
        shader/diffuse_vert.glsl shader/diffuse_frag.glsl
        shader/texture_vert.glsl shader/texture_frag.glsl
        shader/light_vert.glsl shader/light_frag.glsl
        shader/phong_vert.glsl shader/phong_frag.glsl
        shader/shadowMap_vert.glsl shader/shadowMap_frag.glsl
        shader/postProcessing_vert.glsl shader/postProcessing_frag.glsl
        )
add_resources(shaders ${PPGSO_SHADER_SRC})

# PPGSO library
add_library(ppgso STATIC
        ppgso/mesh.cpp
        ppgso/tiny_obj_loader.cpp
        ppgso/shader.cpp
        ppgso/image.cpp
        ppgso/image_bmp.cpp
        ppgso/image_raw.cpp
        ppgso/texture.cpp
        ppgso/window.cpp
        )

# Make sure GLM uses radians and GLEW is a static library
target_compile_definitions(ppgso PUBLIC -DGLM_FORCE_RADIANS -DGLEW_STATIC)

# Link to GLFW, GLEW and OpenGL
target_link_libraries(ppgso PUBLIC ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
# Pass on include directories
target_include_directories(ppgso PUBLIC
        ppgso
        ${GLFW_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
        ${GLM_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR})

#
# TARGETS
#

# raw1_gradient
add_executable(raw1_gradient src/raw1_gradient/raw1_gradient.cpp)
target_link_libraries(raw1_gradient ppgso)
install(TARGETS raw1_gradient DESTINATION .)

# raw2_raycast
add_executable(raw2_raycast src/raw2_raycast/raw2_raycast.cpp)
target_link_libraries(raw2_raycast ppgso)
install(TARGETS raw2_raycast DESTINATION .)

# raw3_raytrace
add_executable(raw3_raytrace src/raw3_raytrace/raw3_raytrace.cpp)
target_link_libraries(raw3_raytrace ppgso ${OpenMP_libomp_LIBRARY})
install(TARGETS raw3_raytrace DESTINATION .)

# raw4_raster
add_executable(raw4_raster src/raw4_raster/raw4_raster.cpp)
target_link_libraries(raw4_raster ppgso)
install(TARGETS raw4_raster DESTINATION .)

# gl1_gradient
add_executable(gl1_gradient src/gl1_gradient/gl1_gradient.cpp src/project/c++/spider.h)
target_link_libraries(gl1_gradient ppgso shaders)
install(TARGETS gl1_gradient DESTINATION .)

# gl2_texture
add_executable(gl2_texture src/gl2_texture/gl2_texture.cpp)
target_link_libraries(gl2_texture ppgso shaders)
install(TARGETS gl2_texture DESTINATION .)

# gl3_animate
add_executable(gl3_animate src/gl3_animate/gl3_animate.cpp)
target_link_libraries(gl3_animate ppgso shaders ${OpenMP_libomp_LIBRARY})
install(TARGETS gl3_animate DESTINATION .)

# gl4_transform
add_executable(gl4_transform src/gl4_transform/gl4_transform.cpp)
target_link_libraries(gl4_transform ppgso shaders)
install(TARGETS gl4_transform DESTINATION .)

# gl5_projection
add_executable(gl5_projection src/gl5_projection/gl5_projection.cpp)
target_link_libraries(gl5_projection ppgso shaders)
install(TARGETS gl5_projection DESTINATION .)

# gl6_mesh
add_executable(gl6_mesh src/gl6_mesh/gl6_mesh.cpp)
target_link_libraries(gl6_mesh ppgso shaders)
install(TARGETS gl6_mesh DESTINATION .)

# gl7_diffuse
add_executable(gl7_diffuse src/gl7_diffuse/gl7_diffuse.cpp)
target_link_libraries(gl7_diffuse ppgso shaders)
install(TARGETS gl7_diffuse DESTINATION .)

# gl8_framebuffer
add_executable(gl8_framebuffer src/gl8_framebuffer/gl8_framebuffer.cpp)
target_link_libraries(gl8_framebuffer ppgso shaders)
install(TARGETS gl8_framebuffer DESTINATION .)

# gl9_scene
add_executable(gl9_scene
        src/gl9_scene/gl9_scene.cpp
        src/gl9_scene/object.cpp
        src/gl9_scene/scene.cpp
        src/gl9_scene/camera.cpp
        src/gl9_scene/asteroid.cpp
        src/gl9_scene/generator.cpp
        src/gl9_scene/player.cpp
        src/gl9_scene/projectile.cpp
        src/gl9_scene/explosion.cpp
        src/gl9_scene/space.cpp)
target_link_libraries(gl9_scene ppgso shaders)
install(TARGETS gl9_scene DESTINATION .)
add_custom_command(TARGET gl9_scene POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/ ${CMAKE_CURRENT_BINARY_DIR})

# TASKs

# task1_filter
add_executable(task1_filter src/task1_filter/task1_filter.cpp)
install(TARGETS task1_filter DESTINATION .)

# task2_bresenham
add_executable(task2_bresenham src/task2_bresenham/task2_bresenham.cpp)
target_link_libraries(task2_bresenham ppgso shaders)
install(TARGETS task2_bresenham DESTINATION .)

# task3_bezier
add_executable(task3_bezier src/task3_bezier/task3_bezier.cpp)
target_link_libraries(task3_bezier ppgso shaders)
install(TARGETS task3_bezier DESTINATION .)

# task4_2dshapes
add_executable(task4_2dshapes src/task4_2dshapes/task4_2dshapes.cpp)
target_link_libraries(task4_2dshapes ppgso shaders)
install(TARGETS task4_2dshapes DESTINATION .)

# task5_3d_origin
add_executable(task5_3d_origin src/task5_3d_origin/task5_3d_origin.cpp)
target_link_libraries(task5_3d_origin ppgso shaders)
install(TARGETS task5_3d_origin DESTINATION .)
add_custom_command(TARGET task5_3d_origin POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/ ${CMAKE_CURRENT_BINARY_DIR})

# task6_bezier_surface
add_executable(task6_bezier_surface src/task6_bezier_surface/task6_bezier_surface.cpp)
target_link_libraries(task6_bezier_surface ppgso shaders)
install(TARGETS task6_bezier_surface DESTINATION .)

# task7_particles
add_executable(task7_particles src/task7_particles/task7_particles.cpp)
target_link_libraries(task7_particles ppgso shaders)
install(TARGETS task7_particles DESTINATION .)
add_custom_command(TARGET task7_particles POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/ ${CMAKE_CURRENT_BINARY_DIR})

# Playground target
add_executable(playground src/playground/playground.cpp)
target_link_libraries(playground ppgso shaders)
install (TARGETS playground DESTINATION .)
add_custom_command(TARGET playground POST_BUILD COMMAND  ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/ ${CMAKE_CURRENT_BINARY_DIR})

# project
add_executable(main
        src/project/c++/main.cpp
        src/project/c++/object.cpp
        src/project/c++/scene.cpp
        src/project/c++/camera.cpp
        src/project/c++/castle/castle.h src/project/c++/castle/castle.cpp
        src/project/c++/castle/castleGate.h src/project/c++/castle/castleGate.cpp
        src/project/c++/castle/castleWall.h src/project/c++/castle/castleWall.cpp
        src/project/c++/castle/castleTowerBase.h src/project/c++/castle/castleTowerBase.cpp
        src/project/c++/castle/castleTowerTop.h src/project/c++/castle/castleTowerTop.cpp
        src/project/c++/clock.h src/project/c++/clock.cpp
        src/project/c++/hourHand.h src/project/c++/hourHand.cpp
        src/project/c++/rock.cpp src/project/c++/rock.h
        src/project/c++/ground.cpp src/project/c++/ground.h
        src/project/c++/tree.cpp src/project/c++/tree.h
        src/project/c++/water.cpp src/project/c++/water.h
        src/project/c++/boat.cpp src/project/c++/boat.h
        src/project/c++/riverGenerator.cpp src/project/c++/riverGenerator.h src/project/c++/log.cpp src/project/c++/log.h src/project/c++/spotLight.h src/project/c++/spotLight.cpp src/project/c++/light.h src/project/c++/light.cpp src/project/c++/lightManager.h src/project/c++/lightManager.cpp src/project/c++/objectMaterial.h src/project/c++/objectMaterial.cpp src/project/materials/glossyMaterial.h src/project/materials/glossyMaterial.cpp src/project/c++/pointLight.h src/project/c++/pointLight.cpp src/project/materials/mattMaterial.cpp src/project/materials/mattMaterial.h src/project/materials/palisadeMaterial.cpp src/project/materials/palisadeMaterial.h src/project/c++/torch.cpp src/project/c++/torch.h src/project/c++/fire.cpp src/project/c++/fire.h src/project/c++/campFire.cpp src/project/c++/campFire.h src/project/c++/lamp.cpp src/project/c++/lamp.h src/project/c++/cannon.cpp src/project/c++/cannon.h src/project/c++/ball.cpp src/project/c++/ball.h src/project/c++/bridgeBase.cpp src/project/c++/bridgeBase.h src/project/c++/bridge.cpp src/project/c++/bridge.h src/project/c++/spider.h src/project/c++/spider.cpp src/project/c++/chestLid.h src/project/c++/chestLid.cpp src/project/c++/chest.h src/project/c++/chest.cpp src/project/c++/keyframeAnimation.cpp src/project/c++/keyframeAnimation.h src/project/c++/curve.h src/project/c++/curve.cpp src/project/c++/animation.h src/project/c++/knight.cpp src/project/c++/knight.h)
target_link_libraries(main ppgso shaders)
install (TARGETS main DESTINATION .)
add_custom_command(TARGET main POST_BUILD COMMAND  ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data/ ${CMAKE_CURRENT_BINARY_DIR})


#
# INSTALLATION
#

file(COPY "data/" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
install(DIRECTORY data/ DESTINATION .)
