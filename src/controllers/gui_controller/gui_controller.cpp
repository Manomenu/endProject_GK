#include "gui_controller.h"

void GuiController::update_data(GuiData& new_data)
{
	memcpy(&data, &new_data, sizeof(GuiData));
}

void GuiController::apply_configuration(CameraSystem& camera_system, SceneController& scene_controller, LightSystem& light_system, MotionSystem& motion_system, ComponentSet<LightComponent>& light_components)
{
	camera_system.change_camera(config.camera.selectedCameraMode);
	scene_controller.change_scene_color(config.scene.selectedTimeMode);
	light_system.change_light_mode(config.scene.selectedTimeMode, scene_controller.get_directional_light(), light_components);
	light_system.change_spot_lights_tilt(config.light.carLightsTilt, scene_controller.get_spot_lights_titlable(), light_components);
	motion_system.change_running(config.scene.motionEnabled);
}

std::string GuiController::camera_id_to_name(uint camera_id)
{
	switch (camera_id)
	{
	case 0:
		return "Free";
	case 1:
		return "Following";
	case 2:
		return "Static";
	default:
		return "Custom";
	}
}

void GuiController::build_gui()
{
	float labelWidth = 170.0f;

	ImGui::SetNextWindowSize(ImVec2(0, 0));

	ImGui::Begin("End Project Manager");

	if (ImGui::BeginTabBar("TabBar"))
	{
		if (ImGui::BeginTabItem("Information"))
		{
			ImGui::SeparatorText("Controls");
			ImGui::Text("Release mouse pointer:");
			ImGui::SameLine(labelWidth);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Hold [Left Alt]");
			ImGui::Text("Free camera control:");
			ImGui::SameLine(labelWidth);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Release [Left Alt]");
			ImGui::Text("Switch tabs:");
			ImGui::SameLine(labelWidth);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Click tab names");

			ImGui::EndTabItem();
		}

		labelWidth = 100;

		if (ImGui::BeginTabItem("Details"))
		{
			ImGui::SeparatorText("Entities count");
			ImGui::Text("Towers:");
			ImGui::SameLine(labelWidth);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%d", data.scene.towers_count);
			ImGui::Text("Cars:");
			ImGui::SameLine(labelWidth);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%d", data.scene.cars_count);
			ImGui::Text("Roads:");
			ImGui::SameLine(labelWidth);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%d", data.scene.roads_count);
			ImGui::Text("Cameras:");
			ImGui::SameLine(labelWidth);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%d", data.scene.cameras_count);
			ImGui::Text("Spot Lights:");
			ImGui::SameLine(labelWidth);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%d", data.scene.spot_lights_count);

			ImGui::SeparatorText("Camera details");
			ImGui::Text("Camera mode:");
			ImGui::SameLine(labelWidth);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%s", camera_id_to_name(data.camera.current_camera).c_str());
			ImGui::Text("Yaw:");
			ImGui::SameLine(labelWidth);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%f", data.camera.yaw);
			ImGui::Text("Pitch:");
			ImGui::SameLine(labelWidth);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%f", data.camera.pitch);
			ImGui::Text("Position:");
			ImGui::SameLine(labelWidth);
			ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "[ %f, %f, %f ]", data.camera.position.x, data.camera.position.y, data.camera.position.z);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Configuration")) 
		{
			ImGui::SeparatorText("Camera Mode");
			if (ImGui::RadioButton("Free", config.camera.selectedCameraMode == 0)) config.camera.selectedCameraMode = 0;
			if (ImGui::RadioButton("Following", config.camera.selectedCameraMode == 1)) config.camera.selectedCameraMode = 1;
			if (ImGui::RadioButton("Static", config.camera.selectedCameraMode == 2)) config.camera.selectedCameraMode = 2;
			
			ImGui::SeparatorText("Day Time");
			if (ImGui::RadioButton("Day", config.scene.selectedTimeMode == 0)) config.scene.selectedTimeMode = 0;
			if (ImGui::RadioButton("Night", config.scene.selectedTimeMode == 1)) config.scene.selectedTimeMode = 1;
			
			ImGui::SeparatorText("Motion");
			if (ImGui::RadioButton("On", config.scene.motionEnabled == true)) config.scene.motionEnabled = true;
			if (ImGui::RadioButton("Off", config.scene.motionEnabled == false)) config.scene.motionEnabled = false;
			
			ImGui::SeparatorText("Car Lights Tilt");
			ImGui::SliderFloat3("", glm::value_ptr(config.light.carLightsTilt), -1.0f, 1.0f);
			if (ImGui::Button("Reset"))
			{
				config.light.carLightsTilt = glm::vec3(0.0f, 0.0f, 0.0f);
			}

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}

	ImGui::End();
}

void GuiController::before_render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
}

void GuiController::after_render(PlatformController& platform_controller)
{
	ImGui::Render();
	glm::ivec2 window_size = platform_controller.get_frame_buffer_size();
	glViewport(0, 0, window_size.x, window_size.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}
}