#include "scene_controller.h"

void SceneController::initialize(EntitiesController& entities_controller, 
	ComponentSet<TransformComponent>& transform_components, 
	ComponentSet<RenderComponent>& render_components,
	ComponentSet<LightComponent>& light_components,
	CameraComponent& camera_component
)
{
	TowerData tower_data;
	tower_data.position = glm::vec3(3, 3, 3);
	create_tower(tower_data, entities_controller, transform_components, render_components);
	
	CameraData camera_data;
	camera_data.position = glm::vec3(3, 3, 3);
	create_camera(camera_data, entities_controller, transform_components, camera_component);

	DirectionalLightData dir_light_data;
	dir_light_data.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	dir_light_data.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	dir_light_data.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	dir_light_data.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
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
	transform.position = tower_data.position;

	RenderComponent& render = render_components[tower];
	ModelManager model_manager;	
	model_manager.load_model_to_render_component(tower_data.mesh_file_path, render);
}

void SceneController::create_camera(CameraData& camera_data, EntitiesController& entities_controller, ComponentSet<TransformComponent>& transform_components, CameraComponent& camera_component)
{
	camera = entities_controller.get_new_id();

	TransformComponent& transform = transform_components[camera];
	transform.position = camera_data.position;

	camera_component.forwards = { 0, 0, -1 };
	camera_component.right = { -1, 0, 0 };
	camera_component.up = { 0, 1, 0 };
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
	// todo continue when there exists place to store proper CubeVertex
}
