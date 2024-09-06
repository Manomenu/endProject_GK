#include "gui_controller.h"

void GuiController::update_data(GuiData& new_data)
{
	memcpy(&data, &new_data, sizeof(GuiData));
}

void GuiController::apply_configuration(CameraSystem& camera_system)
{
	camera_system.change_camera(config.camera.selectedCameraMode);
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
	ImGui::Begin("End Project Manager");

	if (ImGui::BeginTabBar("TabBar"))
	{
		if (ImGui::BeginTabItem("Details"))
		{
			ImGui::SeparatorText("Entities count");
			ImGui::Text("Towers:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%d", data.scene.towers_count);

			ImGui::SeparatorText("Camera details");
			ImGui::Text("Camera mode:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%s", camera_id_to_name(data.camera.current_camera).c_str());
			ImGui::Text("Yaw:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%f", data.camera.yaw);
			ImGui::Text("Pitch:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%f", data.camera.pitch);
			ImGui::Text("Position:");
			ImGui::SameLine();
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "[ %f, %f, %f ]", data.camera.position.x, data.camera.position.y, data.camera.position.z);

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Configuration")) 
		{
			ImGui::SeparatorText("Camera Mode");
			if (ImGui::RadioButton("Free", config.camera.selectedCameraMode == 0)) config.camera.selectedCameraMode = 0;
			if (ImGui::RadioButton("Following", config.camera.selectedCameraMode == 1)) config.camera.selectedCameraMode = 1;
			if (ImGui::RadioButton("Static", config.camera.selectedCameraMode == 2)) config.camera.selectedCameraMode = 2;

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