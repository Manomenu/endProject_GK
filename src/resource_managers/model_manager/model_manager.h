#pragma once
#include <config.h>
#include "internal/mesh/mesh.h"

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals |  aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs)

struct ModelManager
{
public:
    void load_model_to_single_mesh(const std::string& file_path);
    const Mesh& get_mesh() { return mesh; }


private:
    Mesh mesh;
    std::vector<Texture> textures_loaded;
    std::string directory;

    void process_node(aiNode* node, const aiScene* scene);
    Mesh process_mesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> load_material_textures(aiMaterial* mat, aiTextureType type, Texture::Type texture_type);
};
