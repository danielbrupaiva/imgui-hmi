#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "core.hpp"
#include <glm/glm.hpp>
#include "glfw_error_handler.hpp"

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
};

class IWindow {
public:
    ~IWindow() = default;
    IWindow() = default;

    virtual bool Create() = 0;
    virtual void Destroy() = 0;
    virtual void Update() = 0;
    [[nodiscard]] virtual bool ShouldClose() const = 0;
    virtual void Close() = 0;
    virtual glm::vec2 GetFramebufferSize() = 0;
};
}

