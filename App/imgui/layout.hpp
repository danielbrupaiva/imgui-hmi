#pragma once

#include "imgui.h"
#include "imgui_stdlib.h"

namespace App::Widget::Layout
{
enum class Position
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

static void set_layout_position(const Layout::Position &layout, const ImVec2 &ctr_position, const ImVec2 &size)
{
	ImVec2 position{0.0f, 0.0f};
	switch (layout) {
		case Layout::Position::NONE: position = ImGui::GetCursorPos();
			break;
		case Layout::Position::WINDOW_CENTER:
			position = {(ImGui::GetWindowSize().x - size.x) * 0.5f,
						(ImGui::GetWindowSize().y - size.y) * 0.5f};
			break;
		case Layout::Position::WINDOW_TOP:
			position = {(ImGui::GetWindowSize().x - size.x) * 0.5f,
						(ImGui::GetWindowSize().y - size.y) * 0.0f};
			break;
		case Layout::Position::WINDOW_BOTTON:
			position = {(ImGui::GetWindowSize().x - size.x) * 0.5f,
						(ImGui::GetWindowSize().y - size.y) * 1.0f};
			break;
		case Layout::Position::WINDOW_LEFT:
			position = {(ImGui::GetWindowSize().x - size.x) * 0.0f,
						(ImGui::GetWindowSize().y - size.y) * 0.5f};
			break;
		case Layout::Position::WINDOW_RIGHT:
			position = {(ImGui::GetWindowSize().x - size.x) * 1.0f,
						(ImGui::GetWindowSize().y - size.y) * 0.5f};
			break;
			//TODO: Implement others strategies
		case Layout::Position::CENTER:break;
		case Layout::Position::TOP:break;
		case Layout::Position::BOTTON:break;
		case Layout::Position::LEFT:break;
		case Layout::Position::RIGHT:break;
	}
	ImGui::SetCursorPos(position);
};
}