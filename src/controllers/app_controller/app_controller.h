// logic for running the program (end project) and also initial configuration for various elements

#pragma once
#include <app_controller/internals/gl_error_handling.h>
#include <gui_controller/gui_controller.h>
#include <platform_controller/platform_controller.h>
#include <transform_component.h>
#include <camera_component.h>
#include <render_system/render_system.h>
#include <camera_system/camera_system.h>
#include <motion_system/motion_system.h>
#include <entities_controller/entities_controller.h>
#include <scene_controller/scene_controller.h>
#include <config.h>
#include <light_system/light_system.h>

struct AppController_Configuration
{
public:
	int default_window_width;
	int default_window_height;
};

struct AppController 
{
public: 
	void initialize(const AppController_Configuration &configuration); 
	void run();

private:
	GLFWwindow* window;

	EntitiesController entities_controller;
	GuiController gui_controller;
	PlatformController platform_controller;
	SceneController scene_controller;

	ShaderManager shader_manager;

	RenderSystem render_system;
	CameraSystem camera_system;
	LightSystem light_system;
	MotionSystem motion_system;

	ComponentSet<TransformComponent> transform_components;
	ComponentSet<RenderComponent> render_components;
	ComponentSet<LightComponent> light_components;
	ComponentSet<MotionComponent> motion_components;
	ComponentSet< CameraComponent> camera_components;
};