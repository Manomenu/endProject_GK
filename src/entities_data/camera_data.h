#pragma once
#include <config.h>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


struct CameraData
{
	glm::vec3 position = glm::vec3(0);
};