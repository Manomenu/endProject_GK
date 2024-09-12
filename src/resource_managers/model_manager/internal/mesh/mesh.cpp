#include "mesh.h"

void Mesh::update(uint VAO, uint EBO, uint VBO, std::vector<Vertex> vertices, std::vector<uint> indices)
{
	glNamedBufferData(VBO, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
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

	glNamedBufferData(EBO, sizeof(uint) * indices.size(), indices.data(), GL_STATIC_DRAW);
	glVertexArrayElementBuffer(VAO, EBO);
}

void Mesh::set_up_buffers()
{
	assert(buffers_set == false);


	glCreateVertexArrays(1, &VAO);

	glCreateBuffers(1, &VBO);
	glNamedBufferData(VBO, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
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
	glNamedBufferData(EBO, sizeof(uint) * indices.size(), indices.data(), GL_STATIC_DRAW);
	glVertexArrayElementBuffer(VAO, EBO);


	buffers_set = true;
}
