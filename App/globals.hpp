#pragma once

#include "logger.hpp"
#include "spec.hpp"

using namespace App;
using namespace Core;

namespace Global {
static Logger logger{"App", spdlog::level::debug};

static const Spec hmi_spec = {
    .backend_type       = eBackend::OPENGLES,
    .shader_version     = GLSL_VERSION["ES 3.0"],
    .title              = "IMGUI HMI",
    .window_size        = ImVec2(),
    .bg_color           = ImVec4(),
    .vsync              = 1
};

};//namespace Global
