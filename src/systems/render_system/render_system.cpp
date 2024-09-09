#include "render_system.h"

void RenderSystem::initialize(ShaderManager& shader_manager)
{
	shader_manager.use();

	glm::mat4 projection = glm::perspective(
		45.0f, 640.0f / 480.0f, 0.02f, 100.0f); // todo move to config
	shader_manager.set_mat4("projection", projection);
}

void RenderSystem::change_fog(ShaderManager& shader_manager, glm::vec3 color, float intensity)
{
	shader_manager.set_vec3("fog.color", color);
	shader_manager.set_float("fog.intensity", intensity);
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
	glm::vec3 scene_color = scene_controller.get_scene_color();

	change_fog(shader_manager, scene_color, scene_controller.get_fog_intensity());

	glViewport(0, 0, window_size.x, window_size.y);
	glClearColor(scene_color.r, scene_color.g, scene_color.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear screen

	for each (std::pair<uint, RenderComponent> data in render_components)
	{
		RenderComponent& render_component = data.second;
		uint entity = data.first;

		set_model(shader_manager, transform_components[entity]);

		for each (const RenderComponent::RenderPart& render_part in render_component.parts)
		{
			shader_manager.set_vec3("material.color_diffuse", render_part.diffuse);
			shader_manager.set_vec3("material.color_specular", render_part.specular);

			if (render_part.diffuse.x == -1)
			{
				glActiveTexture(GL_TEXTURE0);
				shader_manager.set_uniform("material.diffuse", 0);
				glBindTexture(GL_TEXTURE_2D, render_part.diffuse_id);

				glActiveTexture(GL_TEXTURE1);
				shader_manager.set_uniform("material.specular", 1);
				glBindTexture(GL_TEXTURE_2D, render_part.specular_id);	
			}

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
	model = glm::rotate(
		model, glm::radians(transform.eulers.y),
		{ 0.0f, 1.0f, 0.0f });
	model = glm::rotate(
		model, glm::radians(transform.eulers.x),
		{ 1.0f, 0.0f, 0.0f });
	model = glm::scale(model, transform.scale);

	shader_manager.set_mat4("model", model);
}
