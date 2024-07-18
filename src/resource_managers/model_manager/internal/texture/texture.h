#pragma once
#include <config.h>

struct Texture
{
    enum class Type
    {
        DIFFUSE,
        SPECULAR
    };

    uint id;
    Type type;
    std::string file_path;
};

namespace texture_management
{
    uint texture_from_file(const std::string& path, const std::string& directory);
}



