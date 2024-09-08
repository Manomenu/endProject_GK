#include "motion_system.h"

void MotionSystem::update(SceneController& scene_controller, 
	ComponentSet<TransformComponent>& transform_components, 
	ComponentSet<MotionComponent>& motion_components, 
	ComponentSet<CameraComponent>& camera_components,
	ComponentSet<LightComponent>& light_components,
	float delta_time)
{
	if (!running) return;

	for each (auto& data in motion_components)
	{
		uint id = data.first;
		const MotionComponent& motion = data.second;
		double time = glfwGetTime() + motion.offset.time;

		TransformComponent& transform = transform_components[id];

		if (motion.circular_move)
		{

			if (camera_components.find(id) == camera_components.end())
			{
				transform.position =
				{
					motion.circle_center.x + motion.circle_radius * glm::cos(time),
					motion.circle_center.y + motion.circle_radius * glm::sin(time),
					motion.circle_center.z
				};

				transform.eulers.z = time * (180.0f / glm::pi<float>()) + 90;

				if (light_components.find(id) != light_components.end())
				{
					glm::vec3 next_position =
					{
						motion.circle_center.x + motion.circle_radius * glm::cos(time + 0.01),
						motion.circle_center.y + motion.circle_radius * glm::sin(time + 0.01),
						motion.circle_center.z
					};

					glm::vec3 direction = glm::normalize(next_position - transform.position);

					LightComponent& light = light_components[id];
					light.direction = direction;
				}
			}
			else
			{
				time -= 0.5;

				CameraComponent& camera = camera_components[id];
				camera.pitch = time * (180.0f / glm::pi<float>()) + 90;

				camera.pitch = std::fmod(camera.pitch, 360.0f);
				if (camera.pitch < 0.0f) {
					camera.pitch += 360.0f;
				}

				transform.position =
				{
					motion.circle_center.x + motion.circle_radius * glm::cos(time),
					motion.circle_center.y + motion.circle_radius * glm::sin(time),
					motion.circle_center.z
				};

				
			}
		}
	}
}