#pragma once
#include <config.h>
#include "../texture/texture.h"
#include "../vertex.h"

struct Mesh
{
public:
    void initialize(
        std::vector<Vertex> vertices,
        std::vector<uint> indices,
        std::vector<Texture> textures
    ) 
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        
        set_up_buffers();
    }

    std::vector<Vertex>& get_vertices() { return vertices; }
    std::vector<uint>& get_indices() { return indices; }
    std::vector<Texture>& get_textures() { return textures; }
    const std::vector<Vertex>& get_vertices() const { return vertices; }
    const std::vector<uint>& get_indices() const { return indices; }
    const std::vector<Texture>& get_textures() const { return textures; }

    const uint& get_VAO() const 
    {
        assert(buffers_set == true);
        return VAO; 
    }

    

private:
    bool buffers_set = false;
    uint VAO = 0, EBO = 0, VBO = 0;
    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    std::vector<Texture> textures;

    void set_up_buffers();
};