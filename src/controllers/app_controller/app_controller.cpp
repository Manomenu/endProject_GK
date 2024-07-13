#pragma once
#include "app_controller.h"


AppController::AppController(const AppController_Configuration &configuration) 
{
	set_up_glfw(configuration.default_window_height, configuration.default_window_width);
}

AppController::~AppController()
{
}

void AppController::run()
{
}

void AppController::set_up_glfw(int default_window_height, int default_window_width)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#if PRODUCTION_BUILD == 0
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
	internals::enable_gl_error_handling();
#endif


	window = glfwCreateWindow(default_window_width, default_window_height, "End Project", nullptr, nullptr);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
	}
}
