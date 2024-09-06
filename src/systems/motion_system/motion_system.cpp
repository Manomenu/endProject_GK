#include "motion_system.h"

void MotionSystem::update(SceneController& scene_controller, ComponentSet<TransformComponent>& transform_components, ComponentSet<MotionComponent>& motion_components, float delta_time)
{
	for each (auto& data in motion_components)
	{
		uint id = data.first;
		const MotionComponent& motion = data.second;

		TransformComponent& transform = transform_components[id];

		if (motion.circular_move)
		{
			transform.position =
			{
				motion.circle_center.x + motion.circle_radius * glm::sin(glfwGetTime()),
				motion.circle_center.y + motion.circle_radius * (1.0f - glm::cos(glfwGetTime())),
				motion.circle_center.z
			};

			transform.eulers.z = glfwGetTime() * (180.0f / glm::pi<float>());
		}
	}
}