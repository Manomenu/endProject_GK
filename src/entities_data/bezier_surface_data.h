#pragma once
#include <config.h>

struct BezierSurfaceData
{
    glm::vec3 position = glm::vec3(0);
    glm::vec3 eulers = glm::vec3(0);
    glm::vec3 scale = glm::vec3(1);

    glm::vec3 color;
    std::vector<std::vector<float>> control_points;
    int density = 5;

    bool animated = false;
};