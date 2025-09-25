#include "ImGuiHMI.hpp"

int main() {

    Core::Application::ApplicationSpecification spec;
    spec.name = "ImGui HMI Application";
    spec.window_spec.fullscreen = false;
    spec.window_spec.width = 1280;
    spec.window_spec.height = 720;
    spec.gl_shader_version = Core::Application::GLSL_VERSION["4.60"];
    spec.glfw_window_hints.clientApi = Core::Application::ClientApi::OpenGl;
    spec.glfw_window_hints.scaleToMonitor = true;
    spec.glfw_window_hints.decorated = true;

    ImGuiHMI app{spec};
    app.Run();

	return EXIT_SUCCESS;
}