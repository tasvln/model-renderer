#include "renderer.h"

namespace rndr
{
  Renderer::Renderer()
  {
    Shade vertexSrc("src/textures/shader.vert");
    string vertexShaderStr = vertexSrc.loadFile();
    vertexShaderSource = vertexShaderStr.c_str();

    Shade fragSrc("src/textures/shader.frag");
    string fragShaderStr = fragSrc.loadFile();
    fragShaderSource = fragShaderStr.c_str();

    // createTriangle();
  }

  Renderer::~Renderer()
  {
    // glDeleteVertexArrays(1, &vao);
    // glDeleteBuffers(1, &vbo);
  }

  void Renderer::createTriangle()
  {
    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f,
    //     0.5f, -0.5f, 0.0f,
    //     0.0f, 0.5f, 0.0f};

    // // Generate VAO & VBO
    // glGenVertexArrays(1, &vao);
    // glGenBuffers(1, &vbo);

    // glBindVertexArray(vao);

    // glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);

    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindVertexArray(0);

    // // Compile Vertex Shader
    // vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // glCompileShader(vertexShader);

    // // Compile Fragment Shader
    // fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragShader, 1, &fragShaderSource, NULL);
    // glCompileShader(fragShader);

    // // Create Shader Program
    // shaderProgram = glCreateProgram();
    // glAttachShader(shaderProgram, vertexShader);
    // glAttachShader(shaderProgram, fragShader);
    // glLinkProgram(shaderProgram);

    // deleteShaders();
  }

  void Renderer::render()
  {
    // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glUseProgram(shaderProgram);
    // glBindVertexArray(vao);
    // glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  void Renderer::deleteShaders()
  {
    if (vertexShader)
    {
      glDeleteShader(vertexShader);
    }
    if (fragShader)
    {
      glDeleteShader(fragShader);
    }
  }
}