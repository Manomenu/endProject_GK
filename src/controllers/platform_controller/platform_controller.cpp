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

glm::vec2 PlatformController::get_cursor_position()
{
	double x = 0, y = 0;
	glfwGetCursorPos(window, &x, &y);

	return glm::vec2(x, y);
}

bool PlatformController::is_pressed(Buttons button)
{
	return glfwGetKey(window, (int)button) == GLFW_PRESS;
}

void PlatformController::center_cursor()
{
	glm::ivec2 window_size = get_frame_buffer_size();
	glfwSetCursorPos(window, (double)window_size.x / 2.0, (double)window_size.y / 2.0);
}

void PlatformController::set_mouse_input_mode(InputMode mode)
{
	if (mode == InputMode::FreeMouse)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}
