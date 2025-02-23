#include "main.h"

void setOrthographicProjectionForText(int width, int height)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, width, height, 0, -1, 1); // This will make the text render in 2D
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

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

  Shader modelShader("src/textures/model.vert", "src/textures/model.frag");
  Shader textShader("src/textures/text.vert", "src/textures/text.frag");

  Model model("src/obj/backpack/backpack.obj");
  // Model model("src/obj/cottage/cottage.obj");

  int counter;

  GlBugUi ui(window.getGLFWwindow(), "src/fonts/inter.ttf");

  vec4 textColor(1.0f, 1.0f, 1.0f, 1.0f);

  ui.addElement<glbugui::Text>(200, 200, "Static Text", textColor);
  // ui.addElement<glbugui::Text>(1.0f, 1.0f, [&]()
  //                              { return "Counter: " + std::to_string(counter); }, textColor);

  while (!window.checkIfClosed())
  {
    counter++;
    processInput(window.getGLFWwindow());
    window.pollEvents();
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render 3D model
    modelShader.use();

    // Apply 3D perspective projection and camera view for model
    mat4 projection = perspective(radians(camera.Zoom), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
    mat4 view = camera.GetViewMatrix();
    modelShader.setMat4("projection", projection);
    modelShader.setMat4("view", view);

    // Render model
    mat4 matModel = mat4(1.0f);
    matModel = translate(matModel, vec3(0.0f, 0.0f, 0.0f));
    matModel = scale(matModel, vec3(1.0f, 1.0f, 1.0f));
    matModel = rotate(matModel, radians(modelRotationY), vec3(0.0f, 1.0f, 0.0f));
    modelShader.setMat4("model", matModel);
    model.draw(modelShader);

    // Switch to orthographic projection for 2D text rendering
    setOrthographicProjectionForText(WINDOW_WIDTH, WINDOW_HEIGHT);

    // Disable depth test to make sure text is rendered above the 3D scene
    glDisable(GL_DEPTH_TEST);

    // Render text
    textShader.use();
    ui.render();

    // Re-enable depth test for 3D rendering
    glEnable(GL_DEPTH_TEST);

    // Swap buffers
    window.swapBuffers();
  }

  return 0;
}