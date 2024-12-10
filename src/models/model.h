#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stb/stb_image.h>

#include "mesh.h"
#include "../shaders/shader.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model 
{
    public:
        // model data
        std::vector<Texture> textures_loaded;
        std::vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection;

        Model(char *path) { loadModel(path); }
        void Draw(Shader &shader);	
    private:

        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
            std::string typeName);
};

#endif