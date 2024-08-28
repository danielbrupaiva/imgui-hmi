#include "globals.hpp"

using namespace App;
using namespace Global;

void debug_screen(App::IMGUI &app)
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
			app.close();
		}
	}
	ImGui::End();
}

static const std::string TAG = "Main";

int main()
{
	logger.debug("IMGUI HMI is running...");

	// Main thread
	while (!hmi.is_close()) {
		try {
			hmi.run([&]()
					{
						debug_screen(hmi);
					});
		}
		catch (...) {
			logger.error("Main thread error");
		}
	}

	logger.debug("IMGUI HMI finished");
	return EXIT_SUCCESS;
}