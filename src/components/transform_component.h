#pragma once
#include <config.h>

struct TransformComponent
{
	glm::vec3 scale = glm::vec3(1);
	glm::vec3 position = glm::vec3(0);
	glm::vec3 eulers = glm::vec3(0);
};