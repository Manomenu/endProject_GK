#pragma once
#include <config.h>
#include "internal/mesh/mesh.h"
#include <render_component.h>

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals |  aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs)

struct ModelManager
{
public:
    void load_model_to_render_component(const std::string& file_path, RenderComponent& render_component);

private:
    std::vector<Texture> textures_loaded;
    std::string directory;

    void process_node(aiNode* node, const aiScene* scene, RenderComponent& render_component);
    void process_mesh(aiMesh* mesh, const aiScene* scene, RenderComponent::RenderPart& render_part);
    std::vector<Texture> load_textures(const aiScene* scene, aiMaterial* mat, aiTextureType type, Texture::Type texture_type);
};
