#pragma once 
#include <config.h>

struct RenderComponent
{
	struct RenderPart
	{
		uint indices_size;
		uint specular_id;
		uint diffuse_id;
		uint mesh_id;
	};
	
	std::vector<RenderPart> parts;
};
