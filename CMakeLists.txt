cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 23)

project(RENDEL VERSION 1.0.0)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/include)

add_executable(RENDEL main.cpp src/glad.c ext/window/window.cpp ext/renderer/renderer.cpp ext/shade/shade.cpp ext/mesh/mesh.cpp ext/model/model.cpp)

target_link_libraries(RENDEL glfw OpenGL::GL glm::glm-header-only assimp::assimp)
