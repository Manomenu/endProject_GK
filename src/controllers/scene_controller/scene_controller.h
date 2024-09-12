// logic for managing scene in the project
#pragma once
#include <config.h>
#include <entities_controller/entities_controller.h>
#include <transform_component.h>
#include <tower_data.h>
#include <car_data.h>
#include <road_data.h>
#include <camera_data.h>
#include <model_manager/model_manager.h>
#include <render_component.h>
#include <model_manager/model_manager.h>
#include <camera_component.h>
#include <light_component.h>
#include <motion_component.h>
#include <entities_data/directional_light_data.h>
#include <entities_data/spot_light_data.h>
#include <bezier_surface_data.h>
#include <animation_component.h>

struct SceneController
{
public:
	void initialize(
		EntitiesController& entities_controller,
		ComponentSet<TransformComponent>& transform_components,
		ComponentSet<RenderComponent>& render_components,
		ComponentSet<LightComponent>& light_components,
		ComponentSet<MotionComponent>& motion_components,
		ComponentSet<CameraComponent>& camera_components,
		ComponentSet<AnimationComponent>& animation_components
	);
	void create_bezier_surface(BezierSurfaceData& bezier_data,
		EntitiesController& entities_controller,
		ComponentSet<TransformComponent>& transform_components,
		ComponentSet<RenderComponent>& render_components,
		ComponentSet<AnimationComponent>& animation_components
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
		ComponentSet<CameraComponent>& camera_components,
		ComponentSet<MotionComponent>& motion_component
	);
	void create_directional_light(
		DirectionalLightData& dir_light_data, 
		EntitiesController& entities_controller, 
		ComponentSet<LightComponent>& light_components);
	void create_spot_light(
		SpotLightData& spot_light_data, 
		EntitiesController& entities_controller, 
		ComponentSet<LightComponent>& light_components,
		ComponentSet<TransformComponent>& transform_components,
		ComponentSet<RenderComponent>& render_components,
		ComponentSet<MotionComponent>& motion_components);
	void change_scene_color(int sceneMode) { if (sceneMode == 0) scene_color = { 0.5f, 0.5f, 0.9f }; else scene_color = { 0.0, 0.0, 0.0 }; }
	void change_fog_intensity(float new_intensity) { fog_intensity = new_intensity; }

	int get_towers_count() { return towers.size(); }
	int get_cars_count() { return cars.size(); }
	int get_roads_count() { return roads.size(); }
	int get_cameras_count() { return cameras.size(); }
	int get_spot_light_count() { return spot_lights.size(); }
	
	float get_fog_intensity() { return fog_intensity; }
	glm::vec3 get_scene_color() { return scene_color; }
	uint get_free_camera() { return cameras[0]; }
	const std::vector<uint>& get_cameras() { return cameras; }
	const std::vector<uint>& get_cars() { return cars; }
	uint get_directional_light() { return directional_light; }
	const std::vector<uint>& get_spot_lights() { return spot_lights; }
	const std::vector<uint>& get_spot_lights_titlable() { return spot_lights_tiltable; }

private:
	std::vector<uint> cars;
	std::vector<uint> towers;
	std::vector<uint> roads;
	std::vector<uint> cubes;
	std::vector<uint> cameras; // 0 - free, 1 - behind car, 2 - static
	std::vector<uint> spot_lights;
	std::vector<uint> spot_lights_tiltable;
	std::vector<uint> bezier_surfaces;
	uint directional_light;
	glm::vec3 scene_color;
	float fog_intensity;
};