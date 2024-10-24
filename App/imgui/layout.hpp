#pragma once

#include "imgui.h"
#include "imgui_stdlib.h"

namespace App::Widget::Layout
{
enum class Gravity
{
	NONE,
	WINDOW_CENTER,
	WINDOW_TOP,
	WINDOW_BOTTON,
	WINDOW_LEFT,
	WINDOW_RIGHT,
	CENTER,
	TOP,
	BOTTON,
	LEFT,
	RIGHT
};

static void set_position(const Layout::Gravity &layout, const ImVec2 &ref_position, const ImVec2 &widget_size)
{
	ImVec2 position{0.0f, 0.0f};
	switch (layout) {
		case Layout::Gravity::NONE: position = ref_position == position ? ImGui::GetCursorPos() : ref_position;
			break;
		case Layout::Gravity::WINDOW_CENTER:
			position = {(ImGui::GetWindowSize().x - widget_size.x) * 0.5f,
						(ImGui::GetWindowSize().y - widget_size.y) * 0.5f};
			break;
		case Layout::Gravity::WINDOW_TOP:
			position = {(ImGui::GetWindowSize().x - widget_size.x) * 0.5f,
						(ImGui::GetWindowSize().y - widget_size.y) * 0.0f};
			break;
		case Layout::Gravity::WINDOW_BOTTON:
			position = {(ImGui::GetWindowSize().x - widget_size.x) * 0.5f,
						(ImGui::GetWindowSize().y - widget_size.y) * 1.0f};
			break;
		case Layout::Gravity::WINDOW_LEFT:
			position = {(ImGui::GetWindowSize().x - widget_size.x) * 0.0f,
						(ImGui::GetWindowSize().y - widget_size.y) * 0.5f};
			break;
		case Layout::Gravity::WINDOW_RIGHT:
			position = {(ImGui::GetWindowSize().x - widget_size.x) * 1.0f,
						(ImGui::GetWindowSize().y - widget_size.y) * 0.5f};
			break;
		case Layout::Gravity::CENTER:
			position = {(ImGui::GetContentRegionAvail().x - widget_size.x) * 0.5f,
						(ImGui::GetContentRegionAvail().y - widget_size.y) * 0.5f};
			break;
		case Layout::Gravity::TOP:
			position = {(ImGui::GetContentRegionAvail().x - widget_size.x) * 0.5f,
						(ImGui::GetContentRegionAvail().y - widget_size.y) * 0.0f};
			break;
		case Layout::Gravity::BOTTON:
			position = {(ImGui::GetContentRegionAvail().x - widget_size.x) * 0.5f,
						(ImGui::GetContentRegionAvail().y - widget_size.y) * 1.0f};
			break;
		case Layout::Gravity::LEFT:
			position = {(ImGui::GetContentRegionAvail().x - widget_size.x) * 0.0f,
						(ImGui::GetContentRegionAvail().y - widget_size.y) * 0.5f};
			break;
		case Layout::Gravity::RIGHT:
			position = {(ImGui::GetContentRegionAvail().x - widget_size.x) * 1.0f,
						(ImGui::GetContentRegionAvail().y - widget_size.y) * 0.5f};
			break;
	}
	ImGui::SetCursorPos(position);
};
}