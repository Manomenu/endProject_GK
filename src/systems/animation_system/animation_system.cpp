#include "animation_system.h"

void AnimationSystem::update(ComponentSet<AnimationComponent>& animation_components, ComponentSet<RenderComponent>& render_components)
{
	for each (auto& data in animation_components)
	{
		float time = glfwGetTime();
		uint id = data.first;
		const AnimationComponent& animation = data.second;

		if (animation.isWaving)
		{
			auto control_points = animation.start_points;

			for (int i = 0; i < control_points.size(); i++)
			{
				for (int j = 0; j < control_points.size(); j++)
				{
					control_points[i][j] = glm::sin(time * animation.start_points[i][j]);
				}
			}

			RenderComponent& render = render_components[id];

			ModelManager manager;
			manager.load_bezier_surface_to_render_component(render, render.parts.front().diffuse, animation.density, control_points, true, render.parts.front().mesh_id, render.parts.front().ebo, render.parts.front().vbo);
		}
	}
}
