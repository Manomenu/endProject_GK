#include "app_controller.h"


void AppController::initialize(const AppController_Configuration &configuration) 
{
#pragma region glfw_setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#if PRODUCTION_BUILD == 0
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

	window = glfwCreateWindow(configuration.default_window_width, configuration.default_window_height, "End Project", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
	}

	glEnable(GL_DEPTH_TEST);

#if PRODUCTION_BUILD == 0
	internals::enable_gl_error_handling();
#endif
#pragma endregion

#pragma region imgui
	#if REMOVE_IMGUI == 0
	ImGui::CreateContext();
	imguiThemes::yellow();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		//style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 0.f;
		style.Colors[ImGuiCol_DockingEmptyBg].w = 0.f;
	}

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 450");
	#endif
#pragma endregion

#pragma region stb_image
	stbi_set_flip_vertically_on_load(true);
#pragma endregion

#pragma region systems_and_managers_and_controllers_setup
	// todo switch to managers except app_controller!
	platform_controller.initialize(window);
	scene_controller.initialize(entities_controller, transform_components, render_components, light_components, motion_components, camera_components, animation_components);
	shader_manager.initialize(SHADERS_PATH "model.vs", SHADERS_PATH "model.fs");
	shader_manager.use();
	render_system.initialize(shader_manager);
	camera_system.initialize(shader_manager, scene_controller.get_cameras());
#pragma endregion
}

void AppController::run()
{
	auto stop = std::chrono::high_resolution_clock::now();

	while (!glfwWindowShouldClose(window)) 
	{
	#pragma region delta_time
		auto start = std::chrono::high_resolution_clock::now();

		float deltaTime = (std::chrono::duration_cast<std::chrono::nanoseconds>(start - stop)).count() / 1000000000.0;
		stop = std::chrono::high_resolution_clock::now();
	#pragma endregion
		
	#pragma region imgui
		#if REMOVE_IMGUI == 0
		gui_controller.before_render();
		#endif
	#pragma endregion

		//systems
		bool should_close = camera_system.update(platform_controller, transform_components, scene_controller.get_cameras(), camera_components, deltaTime);
		if (should_close) glfwSetWindowShouldClose(window, true);
		animation_system.update(animation_components, render_components);
		motion_system.update(scene_controller, transform_components, motion_components, camera_components, light_components, deltaTime);
		light_system.update(shader_manager, light_components, transform_components);
		render_system.update(shader_manager, platform_controller, scene_controller, transform_components, render_components);

	#pragma region imgui
		#if REMOVE_IMGUI == 0
		GuiData gui_data;
		gui_data.scene.spot_lights_count = scene_controller.get_spot_light_count();
		gui_data.scene.cameras_count = scene_controller.get_cameras_count();
		gui_data.scene.roads_count = scene_controller.get_roads_count();
		gui_data.scene.cars_count = scene_controller.get_cars_count();
		gui_data.scene.towers_count = scene_controller.get_towers_count();
		gui_data.camera.pitch = camera_components[camera_system.get_current_camera()].pitch;
		gui_data.camera.yaw = camera_components[camera_system.get_current_camera()].yaw;
		gui_data.camera.position = transform_components[camera_system.get_current_camera()].position;
		gui_data.camera.current_camera = camera_system.get_camera_array_number(camera_system.get_current_camera(), scene_controller.get_cameras());

		gui_controller.update_data(gui_data);
		gui_controller.apply_configuration(camera_system, scene_controller, light_system, motion_system, light_components);
		gui_controller.build_gui();
		#endif
	#pragma endregion

	#pragma region window stuff

		#pragma region imgui
			#if REMOVE_IMGUI == 0
			gui_controller.after_render(platform_controller);
			#endif
		#pragma endregion

		glfwSwapBuffers(window);
		glfwPollEvents();

	#pragma endregion
	}
}
