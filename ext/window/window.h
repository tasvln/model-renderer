#ifndef WINDOW_H
#define WINDOW_H

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
    static void framebufferSizeCallback(GLFWwindow *window, int width, int height);

  public:
    Window(int width, int height, const string &title);
    ~Window();

    // getters
    bool checkIfClosed() const;
    void pollEvents() const;
    void swapBuffers() const;
    GLFWwindow *getGLFWwindow() const;

    // triggers

    // functions
    void clear();
    void framebufferSizeCallback(GLFWwindow *window, int width, int height);
  };
}

#endif