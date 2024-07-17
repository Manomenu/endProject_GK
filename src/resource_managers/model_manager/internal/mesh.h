#pragma once
#include <config.h>
#include "texture.h"
#include "vertex.h"

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
    }

private:
    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    std::vector<Texture> textures;
};