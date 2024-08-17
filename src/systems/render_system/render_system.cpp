#include "render_system.h"

void RenderSystem::initialize(ShaderManager& shader_manager)
{
	shader_manager.use();

	glm::mat4 projection = glm::perspective(
		45.0f, 640.0f / 480.0f, 0.1f, 10.0f); // todo move to config
	shader_manager.set_mat4("projection", projection);
}

void RenderSystem::update(
	ShaderManager& shader_manager,
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

		set_model(shader_manager, transform_components[entity]);

		for each (const RenderComponent::RenderPart& render_part in render_component.parts)
		{
			glActiveTexture(GL_TEXTURE0);
			shader_manager.set_uniform("material.diffuse", 0);
			glBindTexture(GL_TEXTURE_2D, render_part.diffuse_id);
			
			glActiveTexture(GL_TEXTURE1);
			shader_manager.set_uniform("material.specular", 1);
			glBindTexture(GL_TEXTURE_2D, render_part.specular_id);

			glBindVertexArray(render_part.mesh_id);
			glDrawElements(GL_TRIANGLES, render_part.indices_size, GL_UNSIGNED_INT, 0); 
		}		
	}
}

void RenderSystem::set_model(ShaderManager& shader_manager, TransformComponent& transform)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, transform.position);
	model = glm::rotate(
		model, glm::radians(transform.eulers.z),
		{ 0.0f, 0.0f, 1.0f });

	shader_manager.set_mat4("model", model);
}
