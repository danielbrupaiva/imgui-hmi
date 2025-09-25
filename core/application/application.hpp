#pragma once

#include <iostream>
#include <vector>

#include "core.hpp"

#include "window.hpp"
#include "layer.hpp"
#include "glfw_window.hpp"

namespace Core::Application {

// GLSL version
static std::map<std::string, std::string> GLSL_VERSION = {
    // OpenGL Desktop
    {"1.10", "#version 110"}, // OpenGL 2.0
    {"1.20", "#version 120"}, // OpenGL 2.1
    {"1.30", "#version 130"}, // OpenGL 3.0
    {"1.40", "#version 140"}, // OpenGL 3.1
    {"1.50", "#version 150"}, // OpenGL 3.2
    {"3.30", "#version 330 core"}, // OpenGL 3.3
    {"4.00", "#version 400 core"}, // OpenGL 4.0
    {"4.10", "#version 410 core"}, // OpenGL 4.1
    {"4.20", "#version 420 core"}, // OpenGL 4.2
    {"4.30", "#version 430 core"}, // OpenGL 4.3
    {"4.40", "#version 440 core"}, // OpenGL 4.4
    {"4.50", "#version 450 core"}, // OpenGL 4.5
    {"4.60", "#version 460 core"}, // OpenGL 4.6
    // OpenGL ES
    {"ES1.00", "#version 100"}, // OpenGL ES 2.0
    {"ES2.00", "#version 100"}, // OpenGL ES 2.0
    {"ES3.00", "#version 300 es"}, // OpenGL ES 3.0
    {"ES3.10", "#version 310 es"}, // OpenGL ES 3.1
    {"ES3.20", "#version 320 es"}  // OpenGL ES 3.2
};


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