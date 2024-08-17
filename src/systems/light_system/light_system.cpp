#include "light_system.h"

void LightSystem::update(ShaderManager& shader_manager, uint directional_light, ComponentSet<LightComponent>& light_components)
{
	set_directional(shader_manager, light_components[directional_light]);
}

void LightSystem::set_directional(ShaderManager& shader_manager, LightComponent& light_component)
{
	shader_manager.set_vec3("dirLight.ambient", light_component.ambient);
	shader_manager.set_vec3("dirLight.diffuse", light_component.diffuse);
	shader_manager.set_vec3("dirLight.direction", light_component.direction);
	shader_manager.set_vec3("dirLight.specular", light_component.specular); // uniform buffers from advanced glsl on learnopengl can be used here
}