#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

using namespace std;

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