#include <config.h>

struct CubeVertex
{
	glm::vec3 position;
	glm::vec3 normal_vector;
	glm::vec3 color;
};

struct CubeData
{
	glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 color = glm::vec3(30.0f, 100.0f, 22.0f);
	float scale = 1.0f;

	const std::vector<CubeVertex>& get_vertices() { return vertices; }
    const std::vector<uint>& get_indices() { return indices; }

    // to delete 
    uint VAO = 0, EBO = 0, VBO = 0;
    void set_up_buffers() {

        // to delete

        glCreateVertexArrays(1, &VAO);

        glCreateBuffers(1, &VBO);
        glNamedBufferData(VBO, sizeof(CubeVertex) * get_vertices().size(), get_vertices().data(), GL_STATIC_DRAW);
        glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(CubeVertex)); // binding point 0

        glEnableVertexArrayAttrib(VAO, 0);
        glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, offsetof(CubeVertex, position));
        glVertexArrayAttribBinding(VAO, 0, 0); // Attribute 0 uses binding point 0

        glEnableVertexArrayAttrib(VAO, 1);
        glVertexArrayAttribFormat(VAO, 1, 3, GL_FLOAT, GL_FALSE, offsetof(CubeVertex, normal_vector));
        glVertexArrayAttribBinding(VAO, 1, 0); // Attribute 1 uses binding point 0

        glEnableVertexArrayAttrib(VAO, 2);
        glVertexArrayAttribFormat(VAO, 2, 3, GL_FLOAT, GL_FALSE, offsetof(CubeVertex, color));
        glVertexArrayAttribBinding(VAO, 2, 0); // Attribute 2 uses binding point 0

        glCreateBuffers(1, &EBO);
        glNamedBufferData(EBO, sizeof(uint) * get_indices().size(), get_indices().data(), GL_STATIC_DRAW);
        glVertexArrayElementBuffer(VAO, EBO);
    }
    void draw() 
    {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, get_indices().size(), GL_UNSIGNED_INT, 0);
    }


private:
	std::vector<CubeVertex> vertices = {
        // Front Face
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}, // 0
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}, // 1
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}, // 2
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}}, // 3

        // Back Face
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}}, // 4
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}}, // 5
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}}, // 6
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f, 0.0f}}, // 7

        // Left Face
        {{-1.0f, -1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}, // 8
        {{-1.0f, -1.0f,  1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}, // 9
        {{-1.0f,  1.0f,  1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}, // 10
        {{-1.0f,  1.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}}, // 11

        // Right Face
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}}, // 12
        {{ 1.0f, -1.0f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}}, // 13
        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}}, // 14
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}}, // 15

        // Top Face
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}}, // 16
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}}, // 17
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}}, // 18
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}}, // 19

        // Bottom Face
        {{-1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}}, // 20
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}}, // 21
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}}, // 22
        {{-1.0f, -1.0f, -1.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}}, // 23
    };

    std::vector<uint> indices = {
        // Front Face
        0, 1, 2,
        2, 3, 0,

        // Back Face
        4, 5, 6,
        6, 7, 4,

        // Left Face
        8, 9, 10,
        10, 11, 8,

        // Right Face
        12, 13, 14,
        14, 15, 12,

        // Top Face
        16, 17, 18,
        18, 19, 16,

        // Bottom Face
        20, 21, 22,
        22, 23, 20
    };

};