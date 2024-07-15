// logic for managing gui

#pragma once
#include <config.h>
#include <platform_controller/platform_controller.h>


struct GuiData
{
	uint towers_count = 0;
};

struct GuiController
{
public:
	void before_render();
	void build_gui();
	void after_render(PlatformController& platform_controller);
	void update_data(GuiData& data);

private:
	GuiData data;
};
