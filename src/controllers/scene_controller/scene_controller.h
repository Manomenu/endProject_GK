// logic for managing scene in the project
#pragma once
#include <config.h>
#include <entities_controller/entities_controller.h>
#include <transform_component.h>
#include <tower_data.h>
#include <camera_data.h>
#include <cube_data.h>
#include <model_manager/model_manager.h>
#include <render_component.h>
#include <model_manager/model_manager.h>
#include <camera_component.h>

struct SceneController
{
public:
	void initialize(
		EntitiesController& entities_controller,
		ComponentSet<TransformComponent>& transform_components,
		ComponentSet<RenderComponent>& render_components,
		CameraComponent& camera_component
	);
	void create_tower(
		TowerData& tower_data,
		EntitiesController& entities_controller,
		ComponentSet<TransformComponent>& transform_components,
		ComponentSet<RenderComponent>& render_components
	);
	void create_camera(
		CameraData& camera_data,
		EntitiesController& entities_controller,
		ComponentSet<TransformComponent>& transform_components,
		CameraComponent& camera_component
	);
	void create_cube(CubeData& cube_data,
		EntitiesController& entities_controller,
		ComponentSet<TransformComponent>& transform_components,
		ComponentSet<RenderComponent>& render_components);

	uint get_towers_count() { return towers.size(); }
	uint get_camera() { return camera; }

private:
	std::vector<uint> towers;
	std::vector<uint> cubes;
	uint camera;
};