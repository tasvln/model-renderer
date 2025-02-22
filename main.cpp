#include "main.h"

int main()
{
  string title = "RenDel";
  Window window(WINDOW_WIDTH, WINDOW_HEIGHT, title);

  Renderer renderer;

  while (!window.checkIfClosed())
  {
    renderer.render();

    window.swapBuffers();
    window.pollEvents();
  }

  return 0;
}