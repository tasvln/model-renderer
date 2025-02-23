#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <iostream>
// #include "stb/stb_image.h"
#include "../shade/shade.h"

using namespace std;
using namespace sde;

namespace rndr
{
  class Renderer
  {
  private:
    unsigned int vertexShader, fragShader, shaderProgram;
    const char *vertexShaderSource, *fragShaderSource;

  public:
    Renderer();
    ~Renderer();

    void createTriangle();
    void render();
    void deleteShaders();
  };
}

#endif