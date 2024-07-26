#include "render_system.h"

void RenderSystem::initialize(ShaderManager& shader_manager)
{
	shader_manager.use();

	model_location = shader_manager.get_model_location();

	uint projLocation = shader_manager.get_projection_location();
	glm::mat4 projection = glm::perspective(
		45.0f, 640.0f / 480.0f, 0.1f, 10.0f); // todo move to config
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void RenderSystem::update(
	PlatformController& platform_controller,
	SceneController& scene_controller,
	ComponentSet<TransformComponent>& transform_components,
	ComponentSet<RenderComponent>& render_components
)
{
	glm::ivec2 window_size = platform_controller.get_frame_buffer_size();

	glViewport(0, 0, window_size.x, window_size.y);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear screen

	for each (std::pair<uint, RenderComponent> data in render_components)
	{
		RenderComponent& render_component = data.second;
		uint entity = data.first;

		TransformComponent& transform = transform_components[entity];
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, transform.position);
		model = glm::rotate(
			model, glm::radians(transform.eulers.z),
			{ 0.0f, 0.0f, 1.0f });
		glUniformMatrix4fv(
			model_location, 1, GL_FALSE,
			glm::value_ptr(model));

		//glBindTexture(GL_TEXTURE_2D, render_component.material);
		glBindVertexArray(render_component.mesh);
		glDrawArrays(GL_TRIANGLES, 0, render_component.mesh_internal_data.get_vertices().size()); // todo make verticescount param in render_comp
	}
}