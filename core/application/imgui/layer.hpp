#pragma once

#include "core.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "application.hpp"
#include "layer.hpp"

#include <utility>
#include "style_sheet.hpp"
#include "font.hpp"

namespace Core::Application::ImGuiImpl {

class Layer : public ILayer {
public:
    ~Layer() override {
        logger.debug("ImGuiLayer destroyed");
    };

    explicit Layer(OpenGLApplication& app) : ILayer("ImGuiLayer"), m_app(app) {
        logger.debug("ImGuiLayer created");
    };

    void OnAttach() override {

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        StyleSheet::SetStyle();

        Font::SetFonts(io);

        auto window = static_cast<GLFWwindow *>(m_app.GetWindow()->Handler());
        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(m_app.GetSpecification().gl_shader_version.c_str());

        logger.debug("ImGuiLayer attached");
    }

    void OnDetach() override {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        logger.debug("ImGuiLayer detached");
    }

    void OnUpdate(double deltaTime_ms) override {
//        logger.debug("ImGuiLayer updated: {} ms -> {} Hz", deltaTime_ms * 1000.0, 1 / deltaTime_ms);
    }

    void OnRender() override {
//        logger.debug("ImGuiLayer rendered");
    };

    void Begin() {
        logger.debug("ImGuiLayer Begin");
    }

    void End() {
        logger.debug("ImGuiLayer End");
    }
private:
    OpenGLApplication& m_app;
};
}