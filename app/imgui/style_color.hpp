#pragma once

#include <imgui.h>

namespace App {
struct StyleColor
{
    ~StyleColor() = default;
    StyleColor(const ImGuiCol idx, const ImVec4& col) : idx(idx), col(col) {}
    StyleColor(const StyleColor&) = default;
    StyleColor& operator=(const StyleColor&) = default;

    ImGuiCol idx;
    ImVec4 col;
};
} // App