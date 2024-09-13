#pragma once

#include "logger.hpp"
#include "spec.hpp"
#include "imgui.hpp"
#include "image.hpp"

using namespace App;

namespace Global
{

static Spec hmi_spec = {
	.backend_type       = BackendType::OPENGLES,
	.shader_version     = GLSL_VERSION["ES 3.0"],
	.title              = "IMGUI HMI",
	.window_size        = ImVec2(1280, 720),
	.bg_color           = ImVec4(0.0f, 0.0f, 0.0f, 1.0f),
	.vsync              = 1
};

static IMGUI hmi{hmi_spec};

static std::map<std::string, std::unique_ptr<Image> > GL_Textures;

};//namespace Global
