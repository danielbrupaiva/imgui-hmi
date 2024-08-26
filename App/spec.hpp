//
// Created by daniel on 8/26/24.
//

#pragma once

#include <iostream>
#include "imgui.h"

namespace App
{
struct Spec
{
    std::string title;
    ImVec2 window_size;
    ImVec4 bg_color;
    int8_t enable_vsync;
};
} // App
