#include "window.h"

namespace win
{
  Window::Window(int width, int height, const string &title)
  {
    if (!glfwInit())
    {
      std::cerr << "Failed to initialize GLFW" << std::endl;
      exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window)
    {
      std::cerr << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  }

  ~Window::Window()
  {
    clear();
  }

  void Window::clear()
  {
    glfwDestroyWindow(window);
    glfwTerminate();
  }

  bool Window::checkIfClosed() const
  {
    return glfwWindowShouldClose(window);
  }

  void Window::pollEvents() const
  {
    glfwPollEvents();
  }

  void Window::swapBuffers() const
  {
    glfwSwapBuffers(window);
  }

  GLFWwindow *Window::getGLFWwindow() const
  {
    return window;
  }

  void Window::framebufferSizeCallback(GLFWwindow *window, int width, int height)
  {
    glViewport(0, 0, width, height);
  }
}