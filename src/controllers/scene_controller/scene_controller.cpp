#include "scene_controller.h"

void SceneController::initialize(EntitiesController& entities_controller, 
	ComponentSet<TransformComponent>& transform_components, 
	ComponentSet<RenderComponent>& render_components,
	ComponentSet<LightComponent>& light_components,
	ComponentSet<MotionComponent>& motion_components,
	ComponentSet<CameraComponent>& camera_components
)
{
	scene_color = { 0.5f, 0.5f, 0.9f };

	TowerData tower_data;
	tower_data.position = glm::vec3(3, 0, 2.87);
	create_tower(tower_data, entities_controller, transform_components, render_components);
	tower_data.position = glm::vec3(3.1, 0, 2.87);
	create_tower(tower_data, entities_controller, transform_components, render_components);
	tower_data.position = glm::vec3(3.2, 0, 2.87);
	tower_data.eulers = glm::vec3(-90, -90, 0);
	create_tower(tower_data, entities_controller, transform_components, render_components);
	tower_data.position = glm::vec3(4.3, 0.3, 3);
	tower_data.eulers = glm::vec3(-90, -90, 0);
	create_tower(tower_data, entities_controller, transform_components, render_components);
	tower_data.position = glm::vec3(11, -0.025, 3);
	tower_data.eulers = glm::vec3(-90, -90, 0);
	tower_data.scale = glm::vec3(10);
	create_tower(tower_data, entities_controller, transform_components, render_components);
	tower_data.position = glm::vec3(21, -0.025, 3);
	tower_data.eulers = glm::vec3(-90, -90, 0);
	tower_data.scale = glm::vec3(20);
	create_tower(tower_data, entities_controller, transform_components, render_components);
	tower_data.position = glm::vec3(41, -0.025, 3);
	tower_data.eulers = glm::vec3(-90, -90, 0);
	tower_data.scale = glm::vec3(60);
	create_tower(tower_data, entities_controller, transform_components, render_components);


	RoadData road_data;
	road_data.position = glm::vec3(3, -0.035, 3);
	create_road(road_data, entities_controller, transform_components, render_components);
	road_data.position = glm::vec3(3.18, -0.035, 3);
	create_road(road_data, entities_controller, transform_components, render_components);
	road_data.position = glm::vec3(3.36, -0.035, 3);
	create_road(road_data, entities_controller, transform_components, render_components);
	road_data.position = glm::vec3(3, 0.6 - 0.016, 3);
	road_data.eulers += glm::vec3(180, 0, 0);
	road_data.scale = glm::vec3(1, 0.3, 0.3);
	create_road(road_data, entities_controller, transform_components, render_components);

	#pragma region car_with_lights
	CarData car_data;
	car_data.position = glm::vec3(3, -0.025, 3);
	car_data.eulers = glm::vec3(0, 90, 0);
	car_data.circular_move = true;
	car_data.circle_radius = 0.3f;
	car_data.circle_center = car_data.position;
	car_data.circle_center.y += car_data.circle_radius;
	create_car(car_data, entities_controller, transform_components, render_components, motion_components);
	SpotLightData spot_light_data;
	spot_light_data.ambient = glm::vec3(0);
	spot_light_data.diffuse = glm::vec3(0.8f, 0.8f, 0.3f);
	spot_light_data.specular = glm::vec3(0.5f, 0.5f, 0.2f);
	spot_light_data.constant = 1.0f;
	spot_light_data.linear = 0.7;
	spot_light_data.quadratic = 1.8;
	spot_light_data.cutOff = glm::cos(glm::radians(12.5f));
	spot_light_data.outerCutOff = glm::cos(glm::radians(17.5f));
	spot_light_data.position = glm::vec3(3, 0.3, 2.96);
	spot_light_data.direction = glm::vec3(0, -1, 0);
	spot_light_data.hasBulb = false;
	spot_light_data.follow.isFollowing = true;
	spot_light_data.follow.target = cars[0];
	spot_light_data.follow.offset.r = -0.003;
	spot_light_data.follow.offset.time = 0.1;
	spot_light_data.follow.offset.space = { 0, 0, 0.01f };
	create_spot_light(spot_light_data, entities_controller,
		light_components, transform_components, render_components, motion_components
	);
	spot_lights_tiltable.push_back(spot_lights.back());
	spot_light_data.follow.offset.space = { 0, 0, -0.01f };
	create_spot_light(spot_light_data, entities_controller,
		light_components, transform_components, render_components, motion_components
	);
	spot_lights_tiltable.push_back(spot_lights.back());
	#pragma endregion
	
	CameraData camera_data;
	camera_data.position = glm::vec3(3, -0.03f, 3.3);
	create_camera(camera_data, entities_controller, transform_components, camera_components, motion_components);
	camera_data.followsEntity = true;
	camera_data.followedEntity = cars[0];
	camera_data.yaw = 0;
	create_camera(camera_data, entities_controller, transform_components, camera_components, motion_components);
	camera_data.followsEntity = false;
	camera_data.followedEntity = 0;
	camera_data.yaw = -90;
	create_camera(camera_data, entities_controller, transform_components, camera_components, motion_components);

	DirectionalLightData dir_light_data;
	dir_light_data.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	dir_light_data.ambient2 = glm::vec3(0.2f);
	dir_light_data.diffuse = glm::vec3(0.65f, 0.65f, 0.65f);
	dir_light_data.diffuse2 = glm::vec3(0);
	dir_light_data.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	dir_light_data.specular2 = glm::vec3(0);
	dir_light_data.direction = glm::vec3(-1.0f, -2.0f, -2.0f);
	create_directional_light(dir_light_data, entities_controller, light_components);

	SpotLightData spot_light_data1;
	spot_light_data1.ambient = glm::vec3(0);
	spot_light_data1.diffuse = glm::vec3(0.8f, 0.3f, 0.3f);
	spot_light_data1.specular = glm::vec3(0.5f, 0.2f, 0.2f);
	spot_light_data1.constant = 1.0f;
	spot_light_data1.linear = 0.7;
	spot_light_data1.quadratic = 1.8;
	spot_light_data1.cutOff = glm::cos(glm::radians(12.5f));
	spot_light_data1.outerCutOff = glm::cos(glm::radians(17.5f));
	spot_light_data1.position = glm::vec3(3, 0.3, 2.96);
	spot_light_data1.direction = glm::vec3(0, -1, 0);
	spot_light_data1.hasBulb = true;
	create_spot_light(spot_light_data1, entities_controller,
		light_components, transform_components, render_components, motion_components
	);
	spot_light_data1.ambient = glm::vec3(0);
	spot_light_data1.diffuse = glm::vec3(0.4f, 0.2f, 0.8f);
	spot_light_data1.specular = glm::vec3(0.4f, 0.2f, 0.8f);
	spot_light_data1.position = glm::vec3(3.2, 0.2, 3.02);
	create_spot_light(spot_light_data1, entities_controller,
		light_components, transform_components, render_components, motion_components
	);

	
}

void SceneController::create_spot_light(
	SpotLightData& light_data,
	EntitiesController& entities_controller,
	ComponentSet<LightComponent>& light_components,
	ComponentSet<TransformComponent>& transform_components,
	ComponentSet<RenderComponent>& render_components, 
	ComponentSet<MotionComponent>& motion_components)
{
	int light = entities_controller.get_new_id();
	spot_lights.push_back(light);

	LightComponent& light_component = light_components[light];
	light_component.ambient = light_data.ambient;
	light_component.diffuse = light_data.diffuse;
	light_component.direction = light_data.direction;
	light_component.specular = light_data.specular;
	light_component.constant = light_data.constant;
	light_component.linear = light_data.linear;
	light_component.isSpotLight = true;
	light_component.quadratic = light_data.quadratic;
	light_component.cutOff = light_data.cutOff;
	light_component.outerCutOff = light_data.outerCutOff;

	TransformComponent& transform = transform_components[light];
	transform.position = light_data.position;
	
	if (light_data.follow.isFollowing)
	{
		MotionComponent& motion = motion_components[light];
		MotionComponent& target_motion = motion_components[light_data.follow.target];
		TransformComponent& target_transform = transform_components[light_data.follow.target];

		motion.offset.time = light_data.follow.offset.time;

		if (target_motion.circular_move)
		{
			motion.circle_center = target_motion.circle_center + light_data.follow.offset.space;
			motion.circle_radius = target_motion.circle_radius + light_data.follow.offset.r;
			motion.circular_move = true;
		}
	}

	if (light_data.hasBulb)
	{
		transform.scale = glm::vec3(0.004f);
		RenderComponent& render = render_components[light];
		ModelManager model_manager;
		model_manager.load_bulb_to_render_component(render, light_data.diffuse + glm::vec3(100.0f));
	}
}

void SceneController::create_directional_light(DirectionalLightData& dir_light_data, EntitiesController& entities_controller, ComponentSet<LightComponent>& light_components)
{
	int light = entities_controller.get_new_id();
	directional_light = light;

	LightComponent& light_component = light_components[light];
	light_component.ambient = dir_light_data.ambient;
	light_component.ambient2 = dir_light_data.ambient2;
	light_component.diffuse = dir_light_data.diffuse;
	light_component.diffuse2 = dir_light_data.diffuse2;
	light_component.direction = dir_light_data.direction;
	light_component.specular = dir_light_data.specular;
	light_component.specular2 = dir_light_data.specular2;
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
	render.parts[2].diffuse += glm::vec3(100);
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
	render.parts[12].diffuse += glm::vec3(100);
	render.parts[11].diffuse += glm::vec3(100);
	render.parts[10].diffuse += glm::vec3(100);

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
	camera_component.yaw = camera_data.yaw;

	if (camera_data.followsEntity)
	{
		// todo move this to motion component!
		camera_component.followsEntity = true;
		camera_component.followedEntity = camera_data.followedEntity;

		MotionComponent& motion = motion_components[camera];
		MotionComponent& followed_entity_motion = motion_components[camera_data.followedEntity];

		if (followed_entity_motion.circular_move)
		{
			motion.circle_center = followed_entity_motion.circle_center;
			motion.circle_radius = followed_entity_motion.circle_radius - 0.09;
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
