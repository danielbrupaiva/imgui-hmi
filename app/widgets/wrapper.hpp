#pragma once

#include <imgui.h>

namespace App::Widget
{
struct Wrapper
{
    virtual ~Wrapper() = default;
    virtual void Image(uint32_t texture_id, const ImVec2 &size) = 0;
    virtual bool Button(std::string_view label, const ImVec2 &size) = 0;
    virtual void ImageButton(std::string_view label, uint32_t texture_id, const ImVec2 &size) = 0;
};

struct WrapperImpl final: public Wrapper
{
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
}