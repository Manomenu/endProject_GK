#include "light_system.h"

void LightSystem::update(ShaderManager& shader_manager, ComponentSet<LightComponent>& light_components, ComponentSet<TransformComponent>& transform_components)
{
	int spot_idx = 0;

	for each (auto& data in light_components)
	{
		uint id = data.first;
		const LightComponent& light = data.second;

		if (light.isSpotLight)
		{
			set_spot(shader_manager, light, transform_components[id], spot_idx++);
		}
		else
		{
			set_directional(shader_manager, light);
		}
	}
}

void LightSystem::change_spot_lights_tilt(glm::vec3 direction_tilt, const std::vector<uint>& spot_lights, ComponentSet<LightComponent>& light_components)
{
	for each (const uint& light in spot_lights)
	{
		light_components[light].user_direction_tilt = direction_tilt;
	}
}

void LightSystem::change_light_mode(int selectedTimeMode, uint light, ComponentSet<LightComponent>& light_components)
{
	LightComponent& component = light_components[light];

	if (selectedTimeMode != component.timeMode)
	{
		component.timeMode = selectedTimeMode;
		std::swap(component.ambient, component.ambient2);
		std::swap(component.diffuse, component.diffuse2);
		std::swap(component.specular, component.specular2);
	}
}

void LightSystem::set_spot(ShaderManager& shader_manager, const LightComponent& light_component, TransformComponent& transform_component, int spot_idx)
{
	std::string idx = std::to_string(spot_idx);
	shader_manager.set_vec3("spotLights[" + idx + "].ambient", light_component.ambient);
	shader_manager.set_vec3("spotLights[" + idx + "].diffuse", light_component.diffuse);
	shader_manager.set_vec3("spotLights[" + idx + "].direction", glm::normalize(light_component.direction + light_component.user_direction_tilt));
	shader_manager.set_vec3("spotLights[" + idx + "].specular", light_component.specular);
	shader_manager.set_vec3("spotLights[" + idx + "].position", transform_component.position);
	shader_manager.set_float("spotLights[" + idx + "].cutOff", light_component.cutOff);
	shader_manager.set_float("spotLights[" + idx + "].outerCutOff", light_component.outerCutOff);
	shader_manager.set_float("spotLights[" + idx + "].constant", light_component.constant);
	shader_manager.set_float("spotLights[" + idx + "].linear", light_component.linear);
	shader_manager.set_float("spotLights[" + idx + "].quadratic", light_component.quadratic);
}

void LightSystem::set_directional(ShaderManager& shader_manager, const LightComponent& light_component)
{
	shader_manager.set_vec3("dirLight.ambient", light_component.ambient);
	shader_manager.set_vec3("dirLight.diffuse", light_component.diffuse);
	shader_manager.set_vec3("dirLight.direction", light_component.direction);
	shader_manager.set_vec3("dirLight.specular", light_component.specular); // uniform buffers from advanced glsl on learnopengl can be used here
}