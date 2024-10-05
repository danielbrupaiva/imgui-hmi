#pragma once

#include <iostream>
#include "imgui.h"
#include "imgui_stdlib.h"
#include "layout.hpp"
#include "font.hpp"

namespace App::Widget
{

static void TextView(const std::string_view label,
					 const Font::Size &font_size = Font::Size::DEFAULT,
					 const Layout::Position &layout = Layout::Position::NONE,
					 const ImVec2 &position = ImVec2(0.0f, 0.0f))
{
	Font::set_font_size(font_size);
	ImVec2 size = ImGui::CalcTextSize(label.data());
	Widget::Layout::set_layout_position(layout, position, size);
	ImGui::Text("%s", label.data());
	Font::clean_font(font_size);
}

static bool InputText(const std::string &label, std::string &text,
					  const std::string &hint = "", const bool &isView = true,
					  const ImGuiInputTextFlags flags = ImGuiInputTextFlags_None)
{
	return ImGui::InputTextWithHint(label.empty() ? "##" : label.c_str(),
									hint.c_str(),
									&text,
									isView ? flags : flags | ImGuiInputTextFlags_Password);
}
}
