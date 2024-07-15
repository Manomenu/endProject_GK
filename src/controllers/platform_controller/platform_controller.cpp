#include "platform_controller.h"

void PlatformController::initialize(GLFWwindow* window)
{
	this->window = window;
}

glm::ivec2 PlatformController::get_frame_buffer_size()
{
	int x = 0, y = 0;
	glfwGetWindowSize(window, &x, &y);
	return { x, y };
}
