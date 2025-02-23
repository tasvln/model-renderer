#define GLAD_GL_IMPLEMENTATION
#include "glad/glad.h"
// #define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glcam/glcam.h>
#include <glshader/glshader.h>

#include <iostream>
#include <string>

#include "ext/window/window.h"
#include "ext/renderer/renderer.h"
#include "ext/model/model.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

using namespace std;
using namespace glm;
using namespace win;
using namespace rndr;
using namespace mdl;

// global variables or settings
const int WINDOW_WIDTH = 1200;
const int WINDOW_HEIGHT = 750;

// camera
Camera camera(vec3(0.0f, 0.0f, 3.0f));
float lastX = WINDOW_WIDTH / 2.0f;
float lastY = WINDOW_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// rotation
bool isMousePressed = false;
float modelRotationX = 0.0f;
float modelRotationY = 0.0f;