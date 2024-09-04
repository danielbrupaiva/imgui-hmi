//
// Created by daniel on 8/26/24.
//

#pragma once

#include <iostream>
#include <map>
#include "imgui.h"

namespace Core
{

enum class BackendType
{
	OPENGL, OPENGLES, VULKAN
};

// GLSL version
static std::map<std::string, std::string> GLSL_VERSION = {
	{"2.0", "#version 110"},
	{"2.1", "#version 120"},
	{"3.0", "#version 130"},
	{"3.1", "#version 140"},
	{"3.2", "#version 150"},
	{"3.3", "#version 330 core"},
	{"4.0", "#version 400 core"},
	{"4.1", "#version 410 core"},
	{"4.2", "#version 410 core"},
	{"4.3", "#version 430 core"},
	{"ES 2.0", "#version 100"},
	{"ES 3.0", "#version 300 es"}
};

struct Spec
{
	BackendType backend_type;
	std::string shader_version = GLSL_VERSION["2.0"];
	std::string title;
	ImVec2 window_size;
	ImVec4 bg_color;
	int8_t vsync;
};
}
