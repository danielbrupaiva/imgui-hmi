#pragma once

#include <iostream>
#include <map>
#include <memory>

#include "core.hpp"
#include <glm/glm.hpp>
#include "glfw_error_handler.hpp"

namespace Core::Application {


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

