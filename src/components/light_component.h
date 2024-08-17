#pragma once
#include <config.h>

struct LightComponent
{
    glm::vec3 ambient;
    glm::vec3 direction;
    glm::vec3 diffuse;
    glm::vec3 specular;
};