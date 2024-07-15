// logic for managing input, window, ...

#pragma once
#include <config.h>

struct PlatformController
{
public:
	void initialize(GLFWwindow* window);
	glm::ivec2 get_frame_buffer_size();

private:
	GLFWwindow* window = nullptr;
};