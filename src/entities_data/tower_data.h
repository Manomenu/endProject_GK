#pragma once
#include <config.h>

struct TowerData
{
	glm::vec3 scale = glm::vec3(3.0f, 3.0f, 3.0f);
	glm::vec3 eulers = glm::vec3(-90, 0, 0);
	glm::vec3 position = glm::vec3(0);
	std::string mesh_file_path = MODELS_PATH "tower/brown_tower.glb";
};