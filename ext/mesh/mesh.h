#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <glshader/glshader.h>
// #include "shader.h"

#define MAX_BONE_INFLUENCE 4

using namespace std;
using namespace glm;

struct Vertex
{
  // position
  vec3 position;
  // normal
  vec3 normal;
  // texCoords
  vec2 texCoords;
  // tangent
  vec3 tangent;
  // bitangent
  vec3 biTangent;
  // bone indexes which will influence this vertex
  int m_BoneIDs[MAX_BONE_INFLUENCE];
  // weights from each bone
  float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture
{
  unsigned int id;
  string type;
  string path;
};

using namespace std;

namespace msh
{
  class Mesh
  {
  private:
    unsigned int VBO, EBO;

    void renMesh();

  public:
    unsigned int VAO;
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    void draw(Shader &shader);
  };
}

#endif