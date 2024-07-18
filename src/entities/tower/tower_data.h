#pragma once
#include <config.h>

struct TowerData
{
	glm::vec3 position = glm::vec3(0);
	std::string mesh_file_path = MODELS_PATH "tower/backpack.obj";
};