// logic for managing scene in the project
#pragma once
#include <config.h>
#include <entities_controller/entities_controller.h>
#include <transform_component.h>
#include <tower/tower_data.h>

struct SceneController
{
public:
	void initialize(
		EntitiesController& entities_controller,
		std::unordered_map<uint, TransformComponent>& transform_components
	);
	void create_tower(
		TowerData& tower_data,
		EntitiesController& entities_controller,
		std::unordered_map<uint, TransformComponent>& transform_components
	);
	uint get_towers_count() { return towers.size(); }

private:
	std::vector<int> towers;
};