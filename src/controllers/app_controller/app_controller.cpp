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
	// todo swithc to managers except app_controller!
	platform_controller.initialize(window);
	scene_controller.initialize(entities_controller, transform_components, render_components, light_components, camera_component);
	shader_manager.initialize(SHADERS_PATH "model.vs", SHADERS_PATH "model.fs");
	shader_manager.use();
	render_system.initialize(shader_manager);
	camera_system.initialize(shader_manager);
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
		bool should_close = camera_system.update(platform_controller, transform_components, scene_controller.get_camera(), camera_component, deltaTime);
		if (should_close) glfwSetWindowShouldClose(window, true);
		light_system.update(shader_manager, scene_controller.get_directional_light(), light_components);
		render_system.update(shader_manager, platform_controller, scene_controller, transform_components, render_components);

	#pragma region imgui
		#if REMOVE_IMGUI == 0
		GuiData gui_data;
		gui_data.scene.towers_count = scene_controller.get_towers_count();
		gui_data.camera.pitch = camera_component.pitch;
		gui_data.camera.yaw = camera_component.yaw;
		gui_data.camera.position = transform_components[scene_controller.get_camera()].position;

		gui_controller.update_data(gui_data);
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
