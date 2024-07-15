#include "render_system.h"

void RenderSystem::update(PlatformController& platform_controller)
{
	glm::ivec2 window_size = platform_controller.get_frame_buffer_size();

	glViewport(0, 0, window_size.x, window_size.y);
	glClear(GL_COLOR_BUFFER_BIT); //clear screen
}