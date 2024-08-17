#include "model_manager.h"

void ModelManager::load_model_to_render_component(const std::string& file_path, RenderComponent& render_component)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(file_path, ASSIMP_LOAD_FLAGS);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::string error_message = std::string("ERROR::ASSIMP:: ") + importer.GetErrorString() + "\n";
        return;
    }

    // retrieve the directory path of the filepath
    directory = file_path.substr(0, file_path.find_last_of('/'));

    process_node(scene->mRootNode, scene, render_component);
}

void ModelManager::process_node(aiNode* node, const aiScene* scene, RenderComponent& render_component)
{
    // process all the node's meshes (if any)
    for (uint i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        
        render_component.parts.resize(render_component.parts.size() + 1);
        process_mesh(mesh, scene, render_component.parts.back());
    }

    // then do the same for each of its children
    for (uint i = 0; i < node->mNumChildren; ++i)
    {
        process_node(node->mChildren[i], scene, render_component);
    }
}

void ModelManager::process_mesh(aiMesh* mesh, const aiScene* scene, RenderComponent::RenderPart& render_part)
{
    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    std::vector<Texture> textures;

    for (uint i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex vertex;
        vertex.position =
        {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };
        vertex.normal_vector =
        {
            mesh->mNormals[i].x,
            mesh->mNormals[i].y,
            mesh->mNormals[i].z
        };
        vertex.texture_coords =
        {
            mesh->mTextureCoords[0][i].x,
            mesh->mTextureCoords[0][i].y
        };
        vertices.push_back(vertex);
    }

    for (uint i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (uint j = 0; j < face.mNumIndices; ++j)
            indices.push_back(face.mIndices[j]);
    }
    
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

        std::vector<Texture> diffuse_textures = 
            load_material_textures(material, aiTextureType_DIFFUSE, Texture::Type::DIFFUSE);
        textures.insert(textures.end(), diffuse_textures.begin(), diffuse_textures.end());
        if (diffuse_textures.size() > 0)
            render_part.diffuse_id = diffuse_textures.back().id;
        else
            render_part.diffuse_id = 0;

        std::vector<Texture> specular_textures = 
            load_material_textures(material, aiTextureType_SPECULAR, Texture::Type::SPECULAR);
        textures.insert(textures.end(), specular_textures.begin(), specular_textures.end());
        if (specular_textures.size() > 0)
            render_part.specular_id = specular_textures.back().id;
        else
            render_part.specular_id = 0;
    }

    Mesh _mesh;
    _mesh.initialize(vertices, indices, textures);

    render_part.mesh_id = _mesh.get_VAO();
    render_part.indices_size = _mesh.get_indices().size();
}

std::vector<Texture> ModelManager::load_material_textures(aiMaterial* mat, aiTextureType type, Texture::Type texture_type)
{
    std::vector<Texture> textures;
    for (uint i = 0; i < mat->GetTextureCount(type); ++i)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (uint j = 0; j < textures_loaded.size(); ++j)
        {
            if (std::strcmp(textures_loaded[j].file_path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            Texture texture;
            texture.id = texture_management::texture_from_file(std::string(str.C_Str()), directory);
            texture.type = texture_type;
            texture.file_path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture); // add to loaded textures
        }
    }
    return textures;
}