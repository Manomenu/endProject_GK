#include "scene_controller.h"

void SceneController::initialize(EntitiesController& entities_controller, ComponentSet<TransformComponent>& transform_components, ComponentSet<RenderComponent>& render_components, CameraComponent& camera_component
)
{
	TowerData tower_data;
	tower_data.position = glm::vec3(3, 3, 3);
	create_tower(tower_data, entities_controller, transform_components, render_components);
	
	CameraData camera_data;
	camera_data.position = glm::vec3(3, 3, 3);
	create_camera(camera_data, entities_controller, transform_components, camera_component);
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

	ModelManager model_manager;
	model_manager.load_model_to_single_mesh(tower_data.mesh_file_path);
	
	RenderComponent& render = render_components[tower];
	render.mesh_internal_data = model_manager.get_mesh();
	render.mesh_internal_data.set_up_buffers();
	const auto& textures = render.mesh_internal_data.get_textures();
	auto it = std::find_if(textures.begin(), textures.end(), [](const Texture& texture) {
		return texture.type == Texture::Type::DIFFUSE;
	});
	if (it != textures.end()) {
		render.material = (*it).id;
	}
	else {
		std::cout << "No diffuse texture found." << std::endl;
	}
	render.mesh = render.mesh_internal_data.get_VAO();
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
