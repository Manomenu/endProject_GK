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

		uint diffuseNr = 1;
		uint specularNr = 1;
		auto& textures = render_component.mesh_internal_data.get_textures();
		for (uint i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number, name;
			Texture::Type type = textures[i].type;
			if (type == Texture::Type::DIFFUSE)
			{
				name = "texture_diffuse";
				number = std::to_string(diffuseNr++);
			}
			else if (type == Texture::Type::SPECULAR)
			{
				name = "texture_specular";
				number = std::to_string(specularNr++); // transfer unsigned int to string
			}

			// now set the sampler to the correct texture unit
			shader_manager.set_uniform((name + number).c_str(), i);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
			break;
		}

		//glBindTexture(GL_TEXTURE_2D, render_component.material); // to refactor instead of this upper logic? move samplers and material to bind to render_component
		glBindVertexArray(render_component.mesh);
		glDrawElements(GL_TRIANGLES, render_component.mesh_internal_data.get_indices().size(), GL_UNSIGNED_INT, 0); // todo make verticescount param in render_comp
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
