// logic for managing input, window, ...

#pragma once
#include <config.h>

enum class InputMode
{
	FreeMouse,
	LockedMouse
};

enum class Buttons
{
	A = 65,
	D = 68,
	S = 83,
	W = 87,
	ESC = 256,
	L_CTRL = 341
};

struct PlatformController
{
public:
	void initialize(GLFWwindow* window);
	glm::ivec2 get_frame_buffer_size();
	glm::vec2 get_cursor_position();
	bool is_pressed(Buttons button);
	void center_cursor();
	void set_mouse_input_mode(InputMode mode);

private:
	GLFWwindow* window = nullptr;
};