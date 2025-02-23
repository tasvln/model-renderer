#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

#include <glcam/glcam.h>

#include "../model/model.h"

#include <stb/stb_image.h>

using namespace std;
using namespace mdl;

namespace win
{
  class Window
  {
  private:
    GLFWwindow *window;

  public:
    Window(int width, int height, const string &title);
    ~Window();

    // getters
    bool checkIfClosed() const;
    GLFWwindow *getGLFWwindow() const;

    // triggers
    void pollEvents() const;
    void swapBuffers() const;

    // functions
    void clear();
  };
}

#endif