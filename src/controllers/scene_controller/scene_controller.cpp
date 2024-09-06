#include "scene_controller.h"

void SceneController::initialize(EntitiesController& entities_controller, 
	ComponentSet<TransformComponent>& transform_components, 
	ComponentSet<RenderComponent>& render_components,
	ComponentSet<LightComponent>& light_components,
	ComponentSet<MotionComponent>& motion_components,
	ComponentSet<CameraComponent>& camera_components
)
{
	TowerData tower_data;
	tower_data.position = glm::vec3(3, 0, 2.87);
	create_tower(tower_data, entities_controller, transform_components, render_components);
	tower_data.position = glm::vec3(3.1, 0, 2.87);
	create_tower(tower_data, entities_controller, transform_components, render_components);
	tower_data.position = glm::vec3(3.2, 0, 2.87);
	create_tower(tower_data, entities_controller, transform_components, render_components);

	RoadData road_data;
	road_data.position = glm::vec3(3, -0.035, 3);
	create_road(road_data, entities_controller, transform_components, render_components);
	road_data.position = glm::vec3(3.18, -0.035, 3);
	create_road(road_data, entities_controller, transform_components, render_components);
	road_data.position = glm::vec3(3.36, -0.035, 3);
	create_road(road_data, entities_controller, transform_components, render_components);

	CarData car_data;
	car_data.position = glm::vec3(3, -0.025, 3);
	car_data.eulers = glm::vec3(0, 90, 0);
	car_data.circular_move = true;
	car_data.circle_center = car_data.position;
	car_data.circle_radius = 0.3f;
	car_data.circle_center.y;
	create_car(car_data, entities_controller, transform_components, render_components, motion_components);
	
	CameraData camera_data;
	camera_data.position = glm::vec3(3, -0.03f, 3.3);
	create_camera(camera_data, entities_controller, transform_components, camera_components, motion_components);
	camera_data.followsEntity = true;
	camera_data.followedEntity = cars[0];
	create_camera(camera_data, entities_controller, transform_components, camera_components, motion_components);
	camera_data.followsEntity = false;
	camera_data.followedEntity = 0;
	create_camera(camera_data, entities_controller, transform_components, camera_components, motion_components);

	DirectionalLightData dir_light_data;
	dir_light_data.ambient = glm::vec3(0.09f, 0.09f, 0.09f);
	dir_light_data.diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
	dir_light_data.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	dir_light_data.direction = glm::vec3(-1.0f, -2.0f, -2.0f);
	create_directional_light(dir_light_data, entities_controller, light_components);
}

void SceneController::create_directional_light(DirectionalLightData& dir_light_data, EntitiesController& entities_controller, ComponentSet<LightComponent>& light_components)
{
	int light = entities_controller.get_new_id();
	directional_light = light;

	LightComponent& light_component = light_components[light];
	light_component.ambient = dir_light_data.ambient;
	light_component.diffuse = dir_light_data.diffuse;
	light_component.direction = dir_light_data.direction;
	light_component.specular = dir_light_data.specular;
}

void SceneController::create_tower(
	TowerData& tower_data, EntitiesController& entities_controller,
	ComponentSet<TransformComponent>& transform_components, ComponentSet<RenderComponent>& render_components
)
{
	int tower = entities_controller.get_new_id();
	towers.push_back(tower);

	TransformComponent& transform = transform_components[tower];
	transform.scale = tower_data.scale;
	transform.position = tower_data.position;
	transform.eulers = tower_data.eulers;

	RenderComponent& render = render_components[tower];
	ModelManager model_manager;	
	model_manager.load_model_to_render_component(tower_data.mesh_file_path, render);
}

void SceneController::create_car(CarData& data, EntitiesController& entities_controller,
	ComponentSet<TransformComponent>& transform_components, ComponentSet<RenderComponent>& render_components, ComponentSet<MotionComponent>& motion_components
)
{
	int car = entities_controller.get_new_id();
	cars.push_back(car);

	TransformComponent& transform = transform_components[car];
	transform.position = data.position;
	transform.eulers = data.eulers;
	transform.scale = data.scale;

	RenderComponent& render = render_components[car];
	ModelManager model_manager;
	model_manager.load_model_to_render_component(data.mesh_file_path, render);

	if (data.circular_move)
	{
		MotionComponent& motion = motion_components[car];
		motion.circular_move = data.circular_move;
		motion.circle_center = data.circle_center;
		motion.circle_radius = data.circle_radius;
	}
}

void SceneController::create_road(RoadData& road_data, EntitiesController& entities_controller,
	ComponentSet<TransformComponent>& transform_components, ComponentSet<RenderComponent>& render_components
)
{
	int road = entities_controller.get_new_id();
	roads.push_back(road);

	TransformComponent& transform = transform_components[road];
	transform.position = road_data.position;
	transform.eulers = road_data.eulers;
	transform.scale = road_data.scale;

	RenderComponent& render = render_components[road];
	ModelManager model_manager;
	model_manager.load_model_to_render_component(road_data.mesh_file_path, render);
}

void SceneController::create_camera(
	CameraData& camera_data, 
	EntitiesController& entities_controller, 
	ComponentSet<TransformComponent>& transform_components, 
	ComponentSet<CameraComponent>& camera_components, 
	ComponentSet<MotionComponent>& motion_components)
{
	uint camera = entities_controller.get_new_id();
	cameras.push_back(camera);

	TransformComponent& transform = transform_components[camera];
	transform.position = camera_data.position;

	CameraComponent& camera_component = camera_components[camera];
	camera_component.forwards = { 0, 0, -1 };
	camera_component.right = { -1, 0, 0 };
	camera_component.up = { 0, 1, 0 };
	camera_component.movement_speed = 0.1f;
	camera_component.yaw = 0;

	if (camera_data.followsEntity)
	{
		camera_component.followsEntity = true;
		camera_component.followedEntity = camera_data.followedEntity;

		MotionComponent& motion = motion_components[camera];
		MotionComponent& followed_entity_motion = motion_components[camera_data.followedEntity];

		if (followed_entity_motion.circular_move)
		{
			motion.circle_center = followed_entity_motion.circle_center;
			motion.circle_center.y + 0.04;
			motion.circle_radius = followed_entity_motion.circle_radius;
			motion.circular_move = true;
		}
	}
}

void SceneController::create_cube(CubeData& cube_data, EntitiesController& entities_controller, 
	ComponentSet<TransformComponent>& transform_components, ComponentSet<RenderComponent>& render_components)
{
	int cube = entities_controller.get_new_id();
	cubes.push_back(cube);

	TransformComponent& transform = transform_components[cube];
	transform.position = cube_data.position;
	transform.eulers = cube_data.rotation;
	
	RenderComponent& render = render_components[cube];
}
