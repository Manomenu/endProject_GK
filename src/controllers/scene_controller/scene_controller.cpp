#include "scene_controller.h"

void SceneController::initialize(
	EntitiesController& entities_controller,
	std::unordered_map<uint, TransformComponent>& transform_components,
	std::unordered_map<uint, RenderComponent>& render_components
)
{
	TowerData tower_data;
	tower_data.position = glm::vec3(1, 1, 0);
	create_tower(tower_data, entities_controller, transform_components, render_components);
}

void SceneController::create_tower(
	TowerData& tower_data,
	EntitiesController& entities_controller,
	std::unordered_map<uint, TransformComponent>& transform_components,
	std::unordered_map<uint, RenderComponent>& render_components
)
{
	int tower = entities_controller.get_new_id();
	towers.push_back(tower);

	TransformComponent transform;
	transform.position = tower_data.position;
	transform_components[tower] = transform;

	ModelManager model_manager;
	model_manager.load_model_to_single_mesh(tower_data.mesh_file_path);
	
	RenderComponent render;
	const auto& textures = model_manager.get_mesh().get_textures();
	auto it = std::find_if(textures.begin(), textures.end(), [](const Texture& texture) {
		return texture.type == Texture::Type::DIFFUSE;
	});
	if (it != textures.end()) {
		render.material = (*it).id;
	}
	else {
		std::cout << "No diffuse texture found." << std::endl;
	}
	render.mesh = model_manager.get_mesh().get_VAO();
	render_components[tower] = render;
}
