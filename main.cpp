#include "main.h"

int main()
{
  string title = "RenDel";
  Window window(WINDOW_WIDTH, WINDOW_HEIGHT, title);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  while (!window.shouldClose())
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}