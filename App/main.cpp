#include "globals.hpp"

using namespace Core;
using namespace Global;

static const std::string TAG = "Main";

void debug_screen(IMGUI *app)
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
static void load_gl_textures_resources(std::map<std::string, std::unique_ptr<Widget::Image> > &textures)
{
	GL_Textures.insert({"morpheus", std::make_unique<Widget::Image>("./resources/morpheus.jpg")});
	//https://www.flaticon.com/br/packs/functional-ui
	GL_Textures.insert({"profile", std::make_unique<Widget::Image>("./resources/profile.png")});
	GL_Textures.insert({"maintenance_person", std::make_unique<Widget::Image>("./resources/maintenance_person.png")});
	GL_Textures.insert({"restricted_person", std::make_unique<Widget::Image>("./resources/restricted_person.png")});
	GL_Textures.insert({"verify_person", std::make_unique<Widget::Image>("./resources/verify_person.png")});
	GL_Textures.insert({"add_person", std::make_unique<Widget::Image>("./resources/add_person.png")});
	GL_Textures.insert({"delete_person", std::make_unique<Widget::Image>("./resources/delete_person.png")});
	GL_Textures.insert({"view_password", std::make_unique<Widget::Image>("./resources/view.png")});
	GL_Textures.insert({"hidden_password", std::make_unique<Widget::Image>("./resources/hidden.png")});
	GL_Textures.insert({"login", std::make_unique<Widget::Image>("./resources/login.png")});
	GL_Textures.insert({"logout", std::make_unique<Widget::Image>("./resources/logout.png")});
	GL_Textures.insert({"hammer", std::make_unique<Widget::Image>("./resources/hammer.png")});
	GL_Textures.insert({"hammer_cristal", std::make_unique<Widget::Image>("./resources/hammer_cristal.png")});
	GL_Textures.insert({"hammer_red", std::make_unique<Widget::Image>("./resources/hammer_red.png")});
	GL_Textures.insert({"close_reject", std::make_unique<Widget::Image>("./resources/close_reject.png")});
	GL_Textures.insert({"warning", std::make_unique<Widget::Image>("./resources/warning.png")});
	GL_Textures.insert({"danger", std::make_unique<Widget::Image>("./resources/danger.png")});

	logger.debug("{}: GL Textures loaded", TAG);
}

int main()
{
	logger.debug("IMGUI HMI is running...");

	// Main thread
	while (!hmi.is_close())
		try {
			hmi.run([&]()
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