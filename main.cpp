#include "main.h"

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    camera.ProcessKeyboard(FORWARD, deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    camera.ProcessKeyboard(LEFT, deltaTime);
  }

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    camera.ProcessKeyboard(RIGHT, deltaTime);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow *window, double xposIn, double yposIn)
{
  float xpos = static_cast<float>(xposIn);
  float ypos = static_cast<float>(yposIn);

  if (firstMouse)
  {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

  lastX = xpos;
  lastY = ypos;

  if (isMousePressed)
  {
    modelRotationX += yoffset * 0.1f;
    modelRotationY += xoffset * 0.1f;
  }

  camera.ProcessMouseMovement(xoffset, yoffset);
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
  if (button == GLFW_MOUSE_BUTTON_LEFT)
  {
    if (action == GLFW_PRESS)
      isMousePressed = true;
    else if (action == GLFW_RELEASE)
      isMousePressed = false;
  }
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
  cout << "Scroll callback triggered: xoffset = " << xoffset << ", yoffset = " << yoffset << endl;

  camera.ProcessMouseScroll(static_cast<float>(yoffset));

  // if (camera.Zoom < 1.0f)
  //   camera.Zoom = 1.0f;
  // if (camera.Zoom > 45.0f)
  //   camera.Zoom = 45.0f;
}

int main()
{
  string title = "rendel";

  Window window(WINDOW_WIDTH, WINDOW_HEIGHT, title);

  glfwSetFramebufferSizeCallback(window.getGLFWwindow(), framebuffer_size_callback);
  glfwSetCursorPosCallback(window.getGLFWwindow(), mouseCallback);
  glfwSetMouseButtonCallback(window.getGLFWwindow(), mouseButtonCallback);
  glfwSetScrollCallback(window.getGLFWwindow(), scrollCallback);
  glfwSetInputMode(window.getGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

  stbi_set_flip_vertically_on_load(true);

  glEnable(GL_DEPTH_TEST);

  // Renderer renderer;

  Shader shader("src/textures/shader.vert", "src/textures/shader.frag");

  Model model("src/obj/backpack/backpack.obj");
  // Model model("src/obj/cottage/cottage.obj");

  while (!window.checkIfClosed())
  {
    processInput(window.getGLFWwindow());
    window.pollEvents();
    // renderer.render();
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();

    // view/projection transformations
    mat4 projection = perspective(radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    mat4 view = camera.GetViewMatrix();
    shader.setMat4("projection", projection);
    shader.setMat4("view", view);

    // render the loaded model
    mat4 matModel = mat4(1.0f);
    matModel = translate(matModel, vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    matModel = scale(matModel, vec3(1.0f, 1.0f, 1.0f));     // it's a bit too big for our scene, so scale it down
    // matModel = rotate(matModel, radians(modelRotationX), vec3(1.0f, 0.0f, 0.0f)); // Rotate around X
    matModel = rotate(matModel, radians(modelRotationY), vec3(0.0f, 1.0f, 0.0f)); // Rotate around the Y axis
    shader.setMat4("model", matModel);
    model.draw(shader);

    window.swapBuffers();
  }

  return 0;
}