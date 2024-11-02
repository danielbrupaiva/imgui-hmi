#pragma once

#include <imgui.h>
#include "layout.hpp"

namespace App::Widget
{
struct Widgets
{
    virtual ~Widgets() = default;
    virtual App::Layout &Layout() = 0;
    virtual void Image(uint32_t texture_id, const ImVec2 &size) = 0;
    virtual bool Button(std::string_view label, const ImVec2 &size) = 0;
    virtual void ImageButton(std::string_view label, uint32_t texture_id, const ImVec2 &size) = 0;
};

class Wrapper: public Widgets
{
    App::Layout m_layout;
public:
    Wrapper() = default;

    App::Layout& Layout() override
    {
        return m_layout;
    };

    void Image(uint32_t texture_id, const ImVec2 &size) override
    {
        ImGui::Image(texture_id, size);
    }

    bool Button(const std::string_view label, const ImVec2 &size) override
    {
        return ImGui::Button(label.data(), size);
    }

    void ImageButton(const std::string_view label, const uint32_t texture_id, const ImVec2 &size) override
    {
        ImGui::ImageButton(label.data(), texture_id, size);
    }
};
};