#include "scene_controller.h"

void SceneController::initialize(
	EntitiesController& entities_controller,
	std::unordered_map<uint, TransformComponent>& transform_components
)
{
	TowerData tower_data;
	tower_data.position = glm::vec3(0);

	create_tower(tower_data, entities_controller, transform_components);
}

void SceneController::create_tower(
	TowerData& tower_data,
	EntitiesController& entities_controller,
	std::unordered_map<uint, TransformComponent>& transform_components
)
{
	int tower = entities_controller.get_new_id();

	towers.push_back(tower);

	TransformComponent transform;
	transform.position = tower_data.position;

	transform_components[tower] = transform;
}
