#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "core.hpp"
#include "layer.hpp"
#include "glfw_window.hpp"

namespace Core::Application {

struct ApplicationSpecification {
    std::string name = "OpenGL Application";
    WindowSpecification window_spec;
    GlfwWindowHints glfw_window_hints;
    std::string gl_shader_version = Core::Application::GLSL_VERSION["3.30"];
};

class OpenGLApplication {
public:
    ~OpenGLApplication() {
        m_window->Destroy();
        glfwTerminate();
        logger.debug("OpenGLApplication destroyed");
    };

    explicit OpenGLApplication(const ApplicationSpecification& specification = ApplicationSpecification())
        : m_specification(specification) {
        // Reserve space for layer stack
        m_layerStack.reserve(MIN_LAYER_STACK_SIZE);

        SetupGraphicBackend(specification.glfw_window_hints);
    }

    virtual void Run() {
        isRunning = true;
        logger.debug("OpenGLApplication started");

        auto lastTime = GetTimeSec();

        while(isRunning) {

            glfwPollEvents();

            if(m_window->ShouldClose()) {
                Stop();
                break;
            }

            auto currentTime = GetTimeSec();
            auto timestep = std::clamp(currentTime - lastTime, 0.001, 0.1);
            lastTime = currentTime;

            std::for_each(m_layerStack.begin(), m_layerStack.end(), [&](const std::unique_ptr<ILayer>& layer) {
                layer->OnUpdate(timestep);
            });

            std::for_each(m_layerStack.begin(), m_layerStack.end(), [&](const std::unique_ptr<ILayer>& layer) {
                layer->OnRender();
            });

            m_window->Update();
        }

    };

    virtual void Stop() {
        isRunning = false;
        logger.debug("OpenGLApplication stopped");
    };

//    virtual void OnEvent(EventType& event) {};
    virtual void OnUpdate(double deltaTime_ms) {};
    virtual void OnRender() {};

    template<typename TLayer>
    requires(std::is_base_of_v<ILayer, TLayer>)
    void PushLayer(OpenGLApplication& app) {
        m_layerStack.emplace_back(std::make_unique<TLayer>(app));
        m_layerStack.back()->OnAttach();
    }

    static double GetTimeSec() { return glfwGetTime(); }

    [[nodiscard]] inline const ApplicationSpecification& GetSpecification() const { return m_specification; }

    std::shared_ptr<IWindow> &GetWindow() {
        return m_window;
    }

private:

    void SetupGraphicBackend(const GlfwWindowHints& hints = GlfwWindowHints()) {
        // Set error callback
        glfwSetErrorCallback(glfw_error_callback);
        // Initialize GLFW
        if (!glfwInit()) { throw Error("GLFW not initialized"); }
        logger.debug("GLFW initialized");
        // Set GLFW window hints
        hints.apply();
        // Create Window
        m_window = GLFW::Create();
        m_window->Init();
    }

private:
    ApplicationSpecification m_specification;
    std::shared_ptr<IWindow> m_window;
    std::vector< std::unique_ptr< Core::Application::ILayer >> m_layerStack;
    const uint32_t MIN_LAYER_STACK_SIZE = 5;
    std::atomic<bool> isRunning = false;
};
}