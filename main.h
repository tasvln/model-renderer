#define GLAD_GL_IMPLEMENTATION
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
// #define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

#include "ext/window/window.h"

using namespace std;
using namespace win;

// global variables
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;