#pragma once
#include <config.h>

struct CarData
{
	bool circular_move = false;
	glm::vec3 circle_center;
	float circle_radius;

	glm::vec3 scale = glm::vec3(0.01, 0.01, 0.01);
	glm::vec3 eulers = glm::vec3(0);
	glm::vec3 position = glm::vec3(0);
	std::string mesh_file_path = MODELS_PATH "car/Nissan GTR.glb";
};