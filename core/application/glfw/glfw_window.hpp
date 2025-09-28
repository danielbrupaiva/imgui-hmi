#pragma once

#include "core.hpp"
#include <map>

#include "glm/glm.hpp"

#include "glfw_error_handler.hpp"
#include "glfw_window_hint.hpp"
#include "imgui.h"

//https://www.glfw.org/documentation.html
//https://www.glfw.org/docs/latest/window_guide.html
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

struct WindowSpecification {
    std::string title = "Application Window";
    int32_t width = 1280;
    int32_t height = 720;
    bool fullscreen = false;
    bool is_resizeable = true;
    bool vsync = true;

    [[nodiscard]] ImVec2 WindowSize() const { return ImVec2(static_cast<float>(width), static_cast<float>(height)); }
};

class IWindow {
public:
    ~IWindow() = default;
    IWindow() = default;

    virtual bool Init() = 0;
    virtual void Destroy() = 0;
    virtual void Update() = 0;
    [[nodiscard]] virtual bool ShouldClose() const = 0;
    virtual void Close() = 0;
    virtual glm::vec2 GetFramebufferSize() = 0;

    virtual void* Handler() = 0;
};

class GLFW : public IWindow,
             public Core::EnableSharedFromThis<GLFW> {
public:
	~GLFW() override {
        Destroy();
        logger.debug("GLFW destroyed");
    };

    explicit GLFW(WindowSpecification specification = WindowSpecification())
        : m_handler(nullptr), m_specification(std::move(specification)) {
    }

	[[nodiscard]] inline GLFWwindow* get_window() const
	{ return m_handler; }

    void Destroy() final {
        if (m_handler) {
            glfwDestroyWindow(m_handler);
            logger.debug("GLFW window destroyed");
            m_handler = nullptr;
        }
    }

    void Update() final {
        glfwSwapBuffers(m_handler);
    }

    [[nodiscard]] bool ShouldClose() const final {
        return glfwWindowShouldClose(m_handler) != 0;
    }

    void Close() final {
        glfwSetWindowShouldClose(m_handler, GLFW_TRUE);
    };

    bool Init() final {

        m_handler = glfwCreateWindow(static_cast<int32_t>(m_specification.WindowSize().x),
                                     static_cast<int32_t>(m_specification.WindowSize().y),
                                     m_specification.title.c_str(),
                                     m_specification.fullscreen ? glfwGetPrimaryMonitor() : nullptr,
                                     nullptr);

        if (nullptr == m_handler) { throw Error("GLFW window not created"); }

        glfwMakeContextCurrent(m_handler);

        glfwSwapInterval(m_specification.vsync ? 1 : 0); // Enable vsync

        return true;
    }

    glm::vec2 GetFramebufferSize() override {
        int32_t width, height;
        glfwGetFramebufferSize(m_handler, &width, &height);
        return { static_cast<float>(width), static_cast<float>(height) };
    };

    [[nodiscard]] inline const WindowSpecification &GetSpecification() const { return m_specification; }

    void *Handler() override {
        return m_handler;
    }

private:
    GLFWwindow* m_handler;
    WindowSpecification m_specification;
};
}