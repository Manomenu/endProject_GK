#pragma once
#include <config.h>
#include <platform_controller/platform_controller.h>
#include <shader_manager/shader_manager.h>
#include <scene_controller/scene_controller.h>

struct RenderSystem
{
public:
	void initialize(ShaderManager& shader_manager);
	void update(
		PlatformController& platform_controller, 
		SceneController& scene_controller, 
		ComponentSet<TransformComponent>& transform_components,
		ComponentSet<RenderComponent>& render_components
	);

private:
	uint model_location;
};