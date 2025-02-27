#include "model.h"

namespace mdl
{
  Model::Model(const string &filePath, bool gamma)
  {
    gammaCorrection = gamma;
    loadModel(filePath);
  }

  void Model::draw(Shader &shader)
  {
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
      meshes[i].draw(shader);
    }
  }

  void Model::loadModel(const string &path)
  {
    // open file with assimp
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
      cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
      return;
    }

    directory = path.substr(0, path.find_last_of('/'));

    // recursive node processor
    processNode(scene->mRootNode, scene);
  }

  // think of it like a binary tree and checking each parent node and child node
  void Model::processNode(aiNode *node, const aiScene *scene)
  {
    // check parent node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
      aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
      meshes.push_back(processMesh(mesh, scene));
    }

    // check child node
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
      processNode(node->mChildren[i], scene);
    }
  }

  Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene)
  {
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Vertex vertex;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
      vec3 vector;

      // positions
      vector.x = mesh->mVertices[i].x;
      vector.y = mesh->mVertices[i].y;
      vector.z = mesh->mVertices[i].z;

      vertex.position = vector;

      if (mesh->HasNormals())
      {
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
      }

      // texture coordinates
      if (mesh->mTextureCoords[0])
      {
        glm::vec2 vec;

        vec.x = mesh->mTextureCoords[0][i].x;
        vec.y = mesh->mTextureCoords[0][i].y;
        vertex.texCoords = vec;

        // tangent
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.tangent = vector;

        // bitangent
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.biTangent = vector;
      }
      else
      {
        vertex.texCoords = glm::vec2(0.0f, 0.0f);
      }
      vertices.push_back(vertex);
    }

    // get the indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
      aiFace face = mesh->mFaces[i];
      // retrieve all indices of the face and store them in the indices vector
      for (unsigned int j = 0; j < face.mNumIndices; j++)
      {
        indices.push_back(face.mIndices[j]);
      }
    }

    // process materials
    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

    // 1. diffuse maps
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // 2. specular maps
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures);
  }

  vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
  {
    vector<Texture> textures;

    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
      aiString str;
      mat->GetTexture(type, i, &str);

      bool check = false;

      for (unsigned int j = 0; j < textures_loaded.size(); j++)
      {
        if (strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
        {
          textures.push_back(textures_loaded[j]);
          check = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
          break;
        }
      }

      // check if it's a new texture
      if (!check)
      {
        Texture texture;
        texture.id = textureFromFile(str.C_Str(), this->directory);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
        textures_loaded.push_back(texture);
      }
    }

    return textures;
  }
}

unsigned int textureFromFile(const char *path, const string &directory, bool gamma)
{
  string filename = string(path);
  filename = directory + '/' + filename;

  unsigned int textureId;
  glGenTextures(1, &textureId);

  int width, height, nrComponents;

  unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

  if (data)
  {
    GLenum format;
    if (nrComponents == 1)
    {
      format = GL_RED;
    }
    else if (nrComponents == 3)
    {
      format = GL_RGB;
    }
    else if (nrComponents == 4)
    {
      format = GL_RGBA;
    }

    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  }
  else
  {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureId;
}