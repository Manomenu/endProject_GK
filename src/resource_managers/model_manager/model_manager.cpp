#include "model_manager.h"

void ModelManager::load_bezier_surface_to_render_component(RenderComponent& render_component, glm::vec3 color, int density, std::vector<std::vector<float>> control_points, bool isUpdate, uint VAO, uint EBO, uint VBO)
{
    render_component.parts.resize(render_component.parts.size() + 1);
    RenderComponent::RenderPart& part = render_component.parts[0];

    
    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    vertices.resize(density + 1);
    float distance = 1.0f / density;
    float eps = 0.00001f;
    for (int u = 0; u <= density; ++u)
    {
        float uLen = u * distance;

        for (int v = 0; v <= density; ++v)
        {
            float vLen = v * distance;
            vertices.push_back(
                {
                    { uLen, vLen, bezier_point_height(uLen, vLen, control_points)},  // vertex position
                    calculate_normal_vec(uLen, vLen, control_points) // vertex normal
                });

            if (u < density && v < density)
            {
                indices.push_back(0 + v + (1 + density) * (0 + u));
                indices.push_back(1 + v + (1 + density) * (0 + u));
                indices.push_back(1 + v + (1 + density) * (1 + u));

                indices.push_back(0 + v + (1 + density) * (0 + u));
                indices.push_back(1 + v + (1 + density) * (1 + u));
                indices.push_back(0 + v + (1 + density) * (1 + u));
            }
        }
    }

    Mesh mesh;
    mesh.initialize(vertices, indices);

    part.diffuse = color;
    part.specular = glm::vec3(color.x * 0.7, color.y * 0.7, color.z * 0.7);
    part.mesh_id = mesh.get_VAO();
    part.indices_size = mesh.get_indices().size();
    part.ebo = mesh.get_EBO();
    part.vbo = mesh.get_VBO();

    
    //if (!isUpdate)
    //{
    //    
    //}
    //else
    //{
    //    mesh.update(VAO, EBO, VBO, vertices, indices);
    //    part.diffuse = color;
    //    part.specular = glm::vec3(color.x * 0.7, color.y * 0.7, color.z * 0.7);
    //    part.indices_size = mesh.get_indices().size();
    //}
}

glm::vec3 ModelManager::calculate_normal_vec(float x, float y, const std::vector<std::vector<float>>& control_points)
{
    glm::vec3 P_u = { 0, 0, 0 };
    glm::vec3 P_v = { 0, 0, 0 };

    std::vector<std::vector<glm::vec2>> plain;
    plain.resize(4);
    for (int u = 0; u < 4; ++u)
    {
        for (int v = 0; v < 4; ++v)
        {
            plain[u].push_back(glm::vec2(
                u * 1.0f / 3.0f,
                v * 1.0f / 3.0f
            ));
        }
    }

    for (int u = 0; u < 3; ++u)
    {
        for (int v = 0; v < 4; ++v)
        {
            P_u.z += (control_points[u + 1][v] - control_points[u][v])
                * B(u, 2, x) * B(v, 3, y);
            P_u.x += (plain[u + 1][v].x - plain[u][v].x)
                * B(u, 2, x) * B(v, 3, y);
            P_u.y += (plain[u + 1][v].y - plain[u][v].y)
                * B(u, 2, x) * B(v, 3, y);
        }
    }

    for (int u = 0; u < 4; ++u)
    {
        for (int v = 0; v < 3; ++v)
        {
            P_v.z += (control_points[u][v + 1] - control_points[u][v])
                * B(u, 3, x) * B(v, 2, y);
            P_v.x += (plain[u][v + 1].x - plain[u][v].x)
                * B(u, 3, x) * B(v, 2, y);
            P_v.y += (plain[u][v + 1].y - plain[u][v].y)
                * B(u, 3, x) * B(v, 2, y);
        }
    }
    
    P_u.x *= 3;
    P_u.y *= 3;
    P_u.z *= 3;
    P_v.x *= 3;
    P_v.y *= 3;
    P_v.z *= 3;

    auto N = glm::normalize(glm::cross(P_v, P_u));
    return N;
}

float ModelManager::bezier_point_height(float uLen, float vLen, const std::vector<std::vector<float>>& control_points)
{
    int control_points_dim_size = control_points.size();
    float height = 0;

    for (int u = 0; u < control_points_dim_size; ++u)
    {
        for (int v = 0; v < control_points_dim_size; ++v)
        {
            height += control_points[u][v] * B(u, control_points_dim_size - 1, uLen) * B(v, control_points_dim_size - 1, vLen);
        }
    }

    return height;
}

int ModelManager::calculateNewtonSymbol(uint n, uint k) {
    if (k > n)
        return 0;

    if (k == 0 || k == n)
        return 1;

    double result = 1;

    for (unsigned int i = 1; i <= k; i++)
    {
        result = result * (n - i + 1) / i;
    }

    return (int)result;
}

float ModelManager::B(int i, int n, float t)
{
    return std::pow(t, i) * std::pow((1 - t), n - i) * calculateNewtonSymbol(n, i);
}

void ModelManager::load_bulb_to_render_component(RenderComponent& render_component, glm::vec3 color)
{
    render_component.parts.resize(render_component.parts.size() + 1);
    RenderComponent::RenderPart& part = render_component.parts[0];

    Mesh mesh;
    std::vector<Vertex> vertices = {
        // Front Face
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}}, // 0
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}}, // 1
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}}, // 2
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}}, // 3

        // Back Face
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}}, // 4
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}}, // 5
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}}, // 6
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}}, // 7

        // Left Face
        {{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}}, // 8
        {{-1.0f, -1.0f,  1.0f}, {-1.0f, 0.0f, 0.0f}}, // 9
        {{-1.0f,  1.0f,  1.0f}, {-1.0f, 0.0f, 0.0f}}, // 10
        {{-1.0f,  1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}}, // 11

        // Right Face
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}}, // 12
        {{ 1.0f, -1.0f,  1.0f}, {1.0f, 0.0f, 0.0f}}, // 13
        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 0.0f}}, // 14
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}}, // 15

        // Top Face
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}}, // 16
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}}, // 17
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}}, // 18
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}}, // 19

        // Bottom Face
        {{-1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f}}, // 20
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f}}, // 21
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}}, // 22
        {{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}}, // 23
    };
    std::vector<uint> indices = {
        // Front Face
        0, 1, 2,
        2, 3, 0,

        // Back Face
        4, 5, 6,
        6, 7, 4,

        // Left Face
        8, 9, 10,
        10, 11, 8,

        // Right Face
        12, 13, 14,
        14, 15, 12,

        // Top Face
        16, 17, 18,
        18, 19, 16,

        // Bottom Face
        20, 21, 22,
        22, 23, 20
    };
    mesh.initialize(vertices, indices);

    part.diffuse = color;
    part.specular = glm::vec3(color.x * 0.1, color.y * 0.1, color.z * 0.1);
    part.mesh_id = mesh.get_VAO();
    part.indices_size = mesh.get_indices().size();
}

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
        
        if (mesh->mTextureCoords[0] != nullptr)
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
            load_textures(scene, material, aiTextureType_DIFFUSE, Texture::Type::DIFFUSE);
        textures.insert(textures.end(), diffuse_textures.begin(), diffuse_textures.end());
        if (diffuse_textures.size() > 0)
            render_part.diffuse_id = diffuse_textures.back().id;
        else
        {
            aiColor3D color;
            material->Get(AI_MATKEY_COLOR_DIFFUSE, color);

            if (color.r + color.g + color.b > 0)
                render_part.diffuse = glm::vec3(color.r, color.g, color.b);
        }

        std::vector<Texture> specular_textures =
            load_textures(scene, material, aiTextureType_SPECULAR, Texture::Type::SPECULAR);
        textures.insert(textures.end(), specular_textures.begin(), specular_textures.end());
        if (specular_textures.size() > 0)
            render_part.specular_id = specular_textures.back().id;
        else
        {
            aiColor3D color;
            material->Get(AI_MATKEY_COLOR_SPECULAR, color);

            if (color.r + color.g + color.b > 0)
                render_part.specular = glm::vec3(color.r, color.g, color.b);
        }
    }

    Mesh _mesh;
    _mesh.initialize(vertices, indices, textures);

    render_part.mesh_id = _mesh.get_VAO();
    render_part.indices_size = _mesh.get_indices().size();
}

std::vector<Texture> ModelManager::load_textures(const aiScene* scene, aiMaterial* mat, aiTextureType type, Texture::Type texture_type)
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
            texture.id = str.C_Str()[0] == '*' ? texture_management::texture_from_embedded(scene->mTextures[0]) : texture_management::texture_from_file(std::string(str.C_Str()), directory);
            texture.type = texture_type;
            texture.file_path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture); // add to loaded textures
        }
    }
    
    return textures;
}