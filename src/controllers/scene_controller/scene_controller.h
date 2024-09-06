// logic for managing scene in the project
#pragma once
#include <config.h>
#include <entities_controller/entities_controller.h>
#include <transform_component.h>
#include <tower_data.h>
#include <car_data.h>
#include <road_data.h>
#include <camera_data.h>
#include <cube_data.h>
#include <model_manager/model_manager.h>
#include <render_component.h>
#include <model_manager/model_manager.h>
#include <camera_component.h>
#include <light_component.h>
#include <motion_component.h>
#include <entities_data/directional_light_data.h>

struct SceneController
{
public:
	void initialize(
		EntitiesController& entities_controller,
		ComponentSet<TransformComponent>& transform_components,
		ComponentSet<RenderComponent>& render_components,
		ComponentSet<LightComponent>& light_components,
		ComponentSet<MotionComponent>& motion_components,
		CameraComponent& camera_component
	);
	void create_tower(
		TowerData& tower_data,
		EntitiesController& entities_controller,
		ComponentSet<TransformComponent>& transform_components,
		ComponentSet<RenderComponent>& render_components
	);
	void create_car(
		CarData& car_data,
		EntitiesController& entities_controller,
		ComponentSet<TransformComponent>& transform_components,
		ComponentSet<RenderComponent>& render_components, 
		ComponentSet<MotionComponent>& motion_components
	);
	void create_road(
		RoadData& road_data,
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
	void create_directional_light(DirectionalLightData& dir_light_data, EntitiesController& entities_controller, ComponentSet<LightComponent>& light_components);

	uint get_towers_count() { return towers.size(); }
	uint get_camera() { return camera; }
	const std::vector<uint>& get_cars() { return cars; }
	uint get_directional_light() { return directional_light; }

private:
	std::vector<uint> cars;
	std::vector<uint> towers;
	std::vector<uint> roads;
	std::vector<uint> cubes;
	uint camera;
	uint directional_light;
};