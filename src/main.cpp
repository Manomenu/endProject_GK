#pragma once
#include <cstdio>
#include <iostream>
#include "controllers/app_controller/app_controller.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#ifdef _WIN32
#include <Windows.h>
#endif
#undef min
#undef max

void turn_on_console()
{
#ifdef _WIN32
#ifdef _MSC_VER 
#if PRODUCTION_BUILD == 0
	AllocConsole();
	(void)freopen("conin$", "r", stdin);
	(void)freopen("conout$", "w", stdout);
	(void)freopen("conout$", "w", stderr);
	std::cout.sync_with_stdio();
#endif
#endif
#endif
}
 
int main()
{
	turn_on_console();

	auto configuration = AppController_Configuration
	{
		500,	// default_window_width
		500,	// default_window_height
	};

	auto app_controller = AppController{ configuration };
	app_controller.run();


	return EXIT_SUCCESS;
}

