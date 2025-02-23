#ifndef MODEL_H
#define MODEL_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glshader/glshader.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "../mesh/mesh.h"

#include <stb/stb_image.h>

using namespace std;
using namespace msh;

namespace mdl
{
  class Model
  {
  public:
    Model(const string &filePath, bool gamma = false);
    void draw(Shader &shader);

  private:
    vector<Texture> textures_loaded; // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;

    bool gammaCorrection;

    void loadModel(const string &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
  };
}

unsigned int textureFromFile(const char *path, const string &directory, bool gamma = false);

#endif