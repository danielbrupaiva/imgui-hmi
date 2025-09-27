#pragma once

#include "core.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "application.hpp"
#include "layer.hpp"

#include "style_sheet.hpp"
#include "font.hpp"
#include "image.hpp"

namespace Core::Application::ImGuiImpl {

class ImGuiLayer : public ILayer {
public:
    ~ImGuiLayer() override {
        logger.debug("ImGuiLayer destroyed");
    };

    explicit ImGuiLayer(OpenGLApplication& app) : ILayer("ImGuiLayer"), m_app(app) {
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
        // In case of GLFW Window hint set to scale to monitor, we need to query the content scale
        float xscale, yscale;
        glfwGetWindowContentScale(window, &xscale, &yscale);
        m_windowSize.x = m_app.GetSpecification().window_spec.WindowSize().x * xscale;
        m_windowSize.y = m_app.GetSpecification().window_spec.WindowSize().y * yscale;

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
        logger.trace("ImGuiLayer updated: {} ms -> {} Hz", deltaTime_ms * 1000.0, 1 / deltaTime_ms);
    }

    void OnRender() override {
        logger.trace("ImGuiLayer rendered");
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Main window
        // Set window position and size according to application window
        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(m_app.GetSpecification().window_spec.fullscreen ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(m_app.GetSpecification().window_spec.fullscreen ? viewport->WorkSize : viewport->Size);

        ImGui::Begin("MainWindow", nullptr, m_flags);
        {
            // Add ImGui objects here
            static bool show_demo_window = true;
            if(show_demo_window) {
                ImGui::ShowDemoWindow(&show_demo_window);
            }

            static auto morpheus = Image::Create("./resources/morpheus.jpg");
            morpheus->operator()(m_windowSize);

        }ImGui::End();
        // End of Dear ImGui frame
        ImGui::Render();
        // Call application render to clear the screen
        m_app.OnRender();
        // Render ImGui Draw Data
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    };

private:

    OpenGLApplication& m_app;
    glm::vec2 m_windowSize;
    ImGuiWindowFlags m_flags = ImGuiWindowFlags_NoDecoration
                                | ImGuiWindowFlags_NoCollapse
                                | ImGuiWindowFlags_NoMove
                                | ImGuiWindowFlags_NoBringToFrontOnFocus;
                        //		| ImGuiWindowFlags_NoBackground;
};
}