#pragma once
#include <config.h>

struct CameraComponent {
    glm::vec3 right;
    glm::vec3 up = { 0.0f, 1.0f, 0.0f };
    glm::vec3 forwards;

    glm::vec3 world_up = { 0.0f, 1.0f, 0.0f };

    float movement_speed = 2.5f;
    float mouse_sensitivity = 0.1f;
    float zoom = 45.0f;

    float yaw = -90.0f;
    float pitch = 0.0f;
};