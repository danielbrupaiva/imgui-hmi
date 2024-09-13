#include "globals.hpp"

using namespace Core;
using namespace Global;

static const std::string TAG = "Main";

void debug_screen(IMGUI *app)
{
	static bool show_demo_window = false;
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::Begin("Debug");
	{
		if (ImGui::Button("IMGUI")) {
			show_demo_window = !show_demo_window;
		}
		if (ImGui::Button("EXIT")) {
			app->close();
		}
	}
	ImGui::End();
}
static void load_gl_textures_resources(std::map<std::string, std::unique_ptr<Image> > &textures)
{
	GL_Textures.insert({"morpheus", std::make_unique<Image>("./resources/morpheus.jpg")});
	//https://www.flaticon.com/br/packs/functional-ui
	GL_Textures.insert({"profile", std::make_unique<Image>("./resources/profile.png")});
	GL_Textures.insert({"maintenance_person", std::make_unique<Image>("./resources/maintenance_person.png")});
	GL_Textures.insert({"restricted_person", std::make_unique<Image>("./resources/restricted_person.png")});
	GL_Textures.insert({"verify_person", std::make_unique<Image>("./resources/verify_person.png")});
	GL_Textures.insert({"add_person", std::make_unique<Image>("./resources/add_person.png")});
	GL_Textures.insert({"delete_person", std::make_unique<Image>("./resources/delete_person.png")});
	GL_Textures.insert({"view_password", std::make_unique<Image>("./resources/view.png")});
	GL_Textures.insert({"hidden_password", std::make_unique<Image>("./resources/hidden.png")});
	GL_Textures.insert({"login", std::make_unique<Image>("./resources/login.png")});
	GL_Textures.insert({"logout", std::make_unique<Image>("./resources/logout.png")});
	GL_Textures.insert({"hammer", std::make_unique<Image>("./resources/hammer.png")});
	GL_Textures.insert({"hammer_cristal", std::make_unique<Image>("./resources/hammer_cristal.png")});
	GL_Textures.insert({"hammer_red", std::make_unique<Image>("./resources/hammer_red.png")});
	GL_Textures.insert({"close_reject", std::make_unique<Image>("./resources/close_reject.png")});
	GL_Textures.insert({"warning", std::make_unique<Image>("./resources/warning.png")});
	GL_Textures.insert({"danger", std::make_unique<Image>("./resources/danger.png")});

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