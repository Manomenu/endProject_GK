// logic for managing gui

#pragma once
#include <config.h>
#include <platform_controller/platform_controller.h>
#include <camera_system/camera_system.h>
#include <scene_controller/scene_controller.h>
#include <light_system/light_system.h>
#include <motion_system/motion_system.h>

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
		int towers_count = 0;
		int cars_count = 0;
		int roads_count = 0;
		int cameras_count = 0;
		int spot_lights_count = 0;
	} scene;
};

struct GuiConfig
{
	struct
	{
		int selectedCameraMode = 0;
	} camera;
	
	struct
	{
		int selectedTimeMode = 0;
		bool motionEnabled = true;
		float fogIntensity = 1.203f;
	} scene;

	struct
	{
		glm::vec3 carLightsTilt = glm::vec3(0);
	} light;
};

struct GuiController
{
public:
	void before_render();
	void build_gui();
	void after_render(PlatformController& platform_controller);
	void update_data(GuiData& data);
	void apply_configuration(
		CameraSystem& camera_system, 
		SceneController& scene_controller, 
		LightSystem& light_system, MotionSystem& motion_system, ComponentSet<LightComponent>& light_components);

private:
	std::string camera_id_to_name(uint camera_id);

	GuiData data;
	GuiConfig config;
};
