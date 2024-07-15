#include "gui_controller.h"

void GuiController::update_data(GuiData& new_data)
{
	data.towers_count = new_data.towers_count;
}

void GuiController::build_gui()
{
	ImGui::Begin("End Project Manager");

	ImGui::SeparatorText("Entities count");
	ImGui::Text("Towers:");
	ImGui::SameLine();
	ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "%d", data.towers_count);

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