#pragma once
#include <config.h>

struct AnimationComponent {
    bool isWaving = false;
    std::vector<std::vector<float>> start_points;
    int density;
    uint VAO, EBO, VBO;
};