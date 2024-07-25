#include "gui_controller.h"

void GuiController::update_data(GuiData& new_data)
{
	memcpy(&data, &new_data, sizeof(GuiData));
}

void GuiController::build_gui()
{
	ImGui::Begin("End Project Manager");

	ImGui::SeparatorText("Entities count");
	ImGui::Text("Towers:");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%d", data.scene.towers_count);

	ImGui::SeparatorText("Camera details");
	ImGui::Text("Yaw:");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%f", data.camera.yaw);
	ImGui::Text("Pitch:");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%f", data.camera.pitch);
	ImGui::Text("Position:");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "[ %f, %f, %f ]", data.camera.position.x, data.camera.position.y, data.camera.position.z);

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