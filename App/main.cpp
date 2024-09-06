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
	logger.debug("{} GL Textures loaded", TAG);
}

int main()
{
	logger.debug("IMGUI HMI is running...");
//	load_gl_textures_resources(GL_Textures);
	auto image = Image("./resources/morpheus.jpg");
	// Main thread
	while (!hmi.is_close())
		try {
			hmi.run([&]()
					{
						image();
//						ImGui::Image(GL_Textures["morpheus"]->ID(), GL_Textures["morpheus"]->get_size());
						debug_screen(&hmi);
					});
		}
		catch (...) {
			logger.error("Main thread error");
		}


	logger.debug("IMGUI HMI finished");
	return EXIT_SUCCESS;
}