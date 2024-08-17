#pragma once
#include <config.h>
#include <shader_manager/shader_manager.h>
#include <scene_controller/scene_controller.h>

struct LightSystem
{
public:
	void update(ShaderManager& shader_manager,
		uint directional_light, // can be later changed for struct of lights from scene_manager
		ComponentSet<LightComponent>& light_components
	);

private:
	void set_directional(ShaderManager& shader_manager, LightComponent& light_component);
};