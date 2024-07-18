#include <config.h>
#include "controllers/app_controller/app_controller.h"



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

	AppController_Configuration configuration;
	configuration.default_window_width = 1600;
	configuration.default_window_height = 900;

	AppController app_controller;

	app_controller.initialize(configuration);
	app_controller.run();


	return EXIT_SUCCESS;
}

