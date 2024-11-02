#include "globals.hpp"

using namespace Core;
using namespace Global;

static const std::string TAG = "Main";

void debug_screen(IMGUImpl *app)
{
	static bool show_demo_window = false;
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::Begin("Debug", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoNav);
	{
		if (ImGui::Button("IMGUI")) {
			show_demo_window = !show_demo_window;
		}
		if (ImGui::Button("SCREEN1")) {
			screen_manager.set_current_state(ScreenManager::eState::SCREEN1);
		}
		ImGui::SameLine();
		if (ImGui::Button("SCREEN2")) {
			screen_manager.set_current_state(ScreenManager::eState::SCREEN2);
		}
		ImGui::SameLine();
		if (ImGui::Button("SCREEN3")) {
			screen_manager.set_current_state(ScreenManager::eState::SCREEN3);
		}
		ImGui::SameLine();
		if (ImGui::Button("SCREEN4")) {
			screen_manager.set_current_state(ScreenManager::eState::SCREEN4);
		}
		ImGui::SameLine();
		if (ImGui::Button("SCREEN5")) {
			screen_manager.set_current_state(ScreenManager::eState::SCREEN5);
		}
		if (ImGui::Button("EXIT")) {
			app->close();
		}
	}
	ImGui::End();
}

int main()
{
	logger.debug("IMGUI HMI is running...");

	// Main thread
	while (!hmi.is_close())
		try {
			hmi.render([&]()
					   {
						   screen_manager.render();
						   debug_screen(&hmi);
					   });
		}
		catch (...) {
			logger.error("Main thread error");
		}

	logger.debug("IMGUI HMI finished");
	return EXIT_SUCCESS;
}