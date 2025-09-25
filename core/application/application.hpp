#pragma once

#include <iostream>
#include <vector>

#include "core.hpp"

#include "window.hpp"
#include "layer.hpp"
#include "glfw_window.hpp"

namespace Core::Application {

struct ApplicationSpecification {
    std::string name = "OpenGL Application";
    WindowSpecification window_spec;
    GlfwWindowHints glfw_window_hints;
    std::string gl_shader_version = Core::Application::GLSL_VERSION["3.30"];
};

class Application : public std::enable_shared_from_this<Application>{
public:
    virtual ~Application() {
        m_window->Destroy();
        glfwTerminate();
        logger.debug("GLFW terminated");
    };

    explicit Application(const ApplicationSpecification& specification = ApplicationSpecification())
        : m_specification(specification) {
        // Reserve space for layer stack
        m_layerStack.reserve(MIN_LAYER_STACK_SIZE);

        InitGLFW(specification.glfw_window_hints);
    }

    void InitGLFW(const GlfwWindowHints& hints = GlfwWindowHints()) {
        // Set error callback
        glfwSetErrorCallback(glfw_error_callback);
        // Initialize GLFW
        if (!glfwInit()) { throw Error("GLFW not initialized"); }
        logger.debug("GLFW initialized");
        // Set GLFW window hints
        hints.apply();
        // Create Window
        m_window = std::make_unique<GLFW>(m_specification.window_spec);
        m_window->Create();
    }


    virtual void Run() {
        isRunning = true;
        logger.debug("Application started");

        while(isRunning) {

            glfwPollEvents();

            if(m_window->ShouldClose()) {
                Stop();
                break;
            }

            std::for_each(m_layerStack.begin(), m_layerStack.end(), [&](const std::unique_ptr<ILayer>& layer) {
                layer->OnUpdate(0.0f);
            });

            std::for_each(m_layerStack.begin(), m_layerStack.end(), [&](const std::unique_ptr<ILayer>& layer) {
                layer->OnRender();
            });

            m_window->Update();
        }

    };

    virtual void Stop() {
        isRunning = false;
        logger.debug("Application stopped");
    };

//    virtual void OnEvent(EventType& event) {};
    virtual void OnUpdate(float ts) {};
    virtual void OnRender() {};

    template<typename TLayer>
    requires(std::is_base_of_v<ILayer, TLayer>)
    void PushLayer() {
        m_layerStack.emplace_back(std::make_unique<TLayer>());
    }

    [[nodiscard]] inline const ApplicationSpecification& GetSpecification() const { return m_specification; }

    std::shared_ptr<Application> Get() {
        return this->shared_from_this();
    }

private:
    ApplicationSpecification m_specification;
    std::unique_ptr<IWindow> m_window;
    std::vector< std::unique_ptr< Core::Application::ILayer >> m_layerStack;
    const uint32_t MIN_LAYER_STACK_SIZE = 5;
    std::atomic<bool> isRunning = false;
};
}