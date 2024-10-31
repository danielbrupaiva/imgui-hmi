#pragma once

#include <functional>

#include "widgets_wrapper.hpp"

namespace App
{
struct IMGUI
{
    virtual ~IMGUI() = default;
    virtual bool init() = 0;
    virtual void shutdown() = 0;
    virtual bool setup_backend() = 0;
    virtual void render(const std::function<void()> &render) = 0;
    virtual App::WidgetsWrapperImpl &widgets() = 0;
};
}
