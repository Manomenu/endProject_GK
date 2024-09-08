#pragma once
#include <config.h>

struct LightComponent
{
    int timeMode = 0;

    glm::vec3 ambient;
    glm::vec3 ambient2;
    glm::vec3 diffuse;
    glm::vec3 diffuse2;
    glm::vec3 specular;
    glm::vec3 specular2;
    glm::vec3 direction;

    bool isSpotLight = false;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;

    glm::vec3 user_direction_tilt = glm::vec3(0);
};