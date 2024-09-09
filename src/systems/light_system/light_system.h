#pragma once
#include <config.h>
#include <shader_manager/shader_manager.h>
#include <scene_controller/scene_controller.h>

struct LightSystem
{
public:
	void update(
		ShaderManager& shader_manager,
		ComponentSet<LightComponent>& light_components, 
		ComponentSet<TransformComponent>& transform_components
	);
	void change_light_mode(int selectedTimeMode, uint light, ComponentSet<LightComponent>& light_components);
	void change_spot_lights_tilt(glm::vec3 direction_tilt, const std::vector<uint>& spot_lights, ComponentSet<LightComponent>& light_components);
	

private:
	void set_directional(ShaderManager& shader_manager, const LightComponent& light_component);
	void set_spot(ShaderManager& shader_manager, const LightComponent& light_component, TransformComponent& transform_component, int spot_idx);
};