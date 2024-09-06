// logic for managing gui

#pragma once
#include <config.h>
#include <platform_controller/platform_controller.h>
#include <camera_system/camera_system.h>

struct GuiData
{
	struct
	{
		float yaw;
		float pitch;
		glm::vec3 position;
		int current_camera;
	} camera;

	struct
	{
		uint towers_count = 0;
	} scene;
};

struct GuiConfig
{
	struct
	{
		int selectedCameraMode = 0;
	} camera;
};

struct GuiController
{
public:
	void before_render();
	void build_gui();
	void after_render(PlatformController& platform_controller);
	void update_data(GuiData& data);
	void apply_configuration(CameraSystem& camera_system);

private:
	std::string camera_id_to_name(uint camera_id);

	GuiData data;
	GuiConfig config;
};
