#pragma once
#include <config.h>

struct RoadData
{
	glm::vec3 scale = glm::vec3(0.3,0.3, 0.3);
	glm::vec3 eulers = glm::vec3(0);
	glm::vec3 position = glm::vec3(0);
	std::string mesh_file_path = MODELS_PATH "road/r.glb";
};