#include "mesh.h"

void mesh_management::merge_meshes(Mesh& destination_mesh, Mesh& merged_mesh)
{
	auto& dst_vert = destination_mesh.get_vertices();
	auto& mrg_vert = merged_mesh.get_vertices();
	dst_vert.insert(dst_vert.end(), mrg_vert.begin(), mrg_vert.end());

	auto& dst_ind = destination_mesh.get_indices();
	auto& mrg_ind = merged_mesh.get_indices();
	dst_ind.insert(dst_ind.end(), mrg_ind.begin(), mrg_ind.end());

	auto& dst_tex = destination_mesh.get_textures();
	auto& mrg_tex = merged_mesh.get_textures();
	dst_tex.insert(dst_tex.end(), mrg_tex.begin(), mrg_tex.end());
}

bool Mesh::set_up_buffers()
{
	if (buffers_set) return false;

	glCreateVertexArrays(1, &VAO);

	glCreateBuffers(1, &VBO);
	glNamedBufferData(VBO, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(Vertex)); // binding point 0
	
	glEnableVertexArrayAttrib(VAO, 0);
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
	glVertexArrayAttribBinding(VAO, 0, 0); // Attribute 0 uses binding point 0

	glEnableVertexArrayAttrib(VAO, 1);
	glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal_vector));
	glVertexArrayAttribBinding(VAO, 1, 0); // Attribute 1 uses binding point 0

	glEnableVertexArrayAttrib(VAO, 2);
	glVertexArrayAttribFormat(VAO, 2, 2, GL_FLOAT, GL_FALSE, offsetof(Vertex, texture_coords));
	glVertexArrayAttribBinding(VAO, 2, 0); // Attribute 2 uses binding point 0
	
	glCreateBuffers(1, &EBO);
	glNamedBufferData(EBO, sizeof(indices), indices.data(), GL_STATIC_DRAW);
	glVertexArrayElementBuffer(VAO, EBO);


	buffers_set = true;
	return true;
}
