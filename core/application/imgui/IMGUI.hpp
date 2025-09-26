#pragma once

#include <functional>
#include "widgets/wrapper.hpp"

namespace Core::Application::ImGuiImpl
{
struct IMGUI
{
    virtual ~IMGUI() = default;
    virtual bool init() = 0;
    virtual void shutdown() = 0;
    virtual bool setup_backend() = 0;
    virtual void render(const std::function<void()> &render) = 0;
    virtual Widget::Widgets &widgets() = 0;
    virtual ILayout &layout() = 0;
};
}
