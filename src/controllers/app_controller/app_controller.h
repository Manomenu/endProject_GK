#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "app_controller/internals/gl_error_handling.h"


struct AppController_Configuration
{
public:
	int default_window_height;
	int default_window_width;
};

class AppController 
{
public: 
	AppController(const AppController_Configuration &configuration); 
	~AppController(); 
	void run(); 

private:
	GLFWwindow* window;

	void set_up_glfw(int default_window_height, int default_window_width);
};