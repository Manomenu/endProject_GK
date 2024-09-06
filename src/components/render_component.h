#pragma once 
#include <config.h>

struct RenderComponent
{
	struct RenderPart
	{
		uint indices_size;
		uint mesh_id;

		uint specular_id = 0;
		uint diffuse_id = 0;
		// or
		glm::vec3 diffuse = { -1.0f,-1.0f,-1.0f };
		glm::vec3 specular = { -1.0f,-1.0f,-1.0f };;
	};
	
	std::vector<RenderPart> parts;
};
