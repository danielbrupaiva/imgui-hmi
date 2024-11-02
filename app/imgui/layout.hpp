#pragma once

#include "imgui.h"

namespace App
{
struct ILayout{
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

	virtual ~ILayout() = default;
	virtual void set_cursor_position(const Gravity &layout, const ImVec2 &ref_position, const ImVec2 &widget_size) = 0;
};

class Layout : public ILayout
{
public:
	Layout() = default;
	void set_cursor_position(const Gravity &layout, const ImVec2 &ref_position, const ImVec2 &widget_size) override
	{
		ImVec2 position{0.0f, 0.0f};
		switch (layout) {
			case Gravity::NONE: position = ref_position == position ? ImGui::GetCursorPos() : ref_position;
			break;
			case Gravity::WINDOW_CENTER:
				position = {(ImGui::GetWindowSize().x - widget_size.x) * 0.5f,
							(ImGui::GetWindowSize().y - widget_size.y) * 0.5f};
			break;
			case Gravity::WINDOW_TOP:
				position = {(ImGui::GetWindowSize().x - widget_size.x) * 0.5f,
							(ImGui::GetWindowSize().y - widget_size.y) * 0.0f};
			break;
			case Gravity::WINDOW_BOTTON:
				position = {(ImGui::GetWindowSize().x - widget_size.x) * 0.5f,
							(ImGui::GetWindowSize().y - widget_size.y) * 1.0f};
			break;
			case Gravity::WINDOW_LEFT:
				position = {(ImGui::GetWindowSize().x - widget_size.x) * 0.0f,
							(ImGui::GetWindowSize().y - widget_size.y) * 0.5f};
			break;
			case Gravity::WINDOW_RIGHT:
				position = {(ImGui::GetWindowSize().x - widget_size.x) * 1.0f,
							(ImGui::GetWindowSize().y - widget_size.y) * 0.5f};
			break;
			case Gravity::CENTER:
				position = {(ImGui::GetContentRegionAvail().x - widget_size.x) * 0.5f,
							(ImGui::GetContentRegionAvail().y - widget_size.y) * 0.5f};
			break;
			case Gravity::TOP:
				position = {(ImGui::GetContentRegionAvail().x - widget_size.x) * 0.5f,
							(ImGui::GetContentRegionAvail().y - widget_size.y) * 0.0f};
			break;
			case Gravity::BOTTON:
				position = {(ImGui::GetContentRegionAvail().x - widget_size.x) * 0.5f,
							(ImGui::GetContentRegionAvail().y - widget_size.y) * 1.0f};
			break;
			case Gravity::LEFT:
				position = {(ImGui::GetContentRegionAvail().x - widget_size.x) * 0.0f,
							(ImGui::GetContentRegionAvail().y - widget_size.y) * 0.5f};
			break;
			case Gravity::RIGHT:
				position = {(ImGui::GetContentRegionAvail().x - widget_size.x) * 1.0f,
							(ImGui::GetContentRegionAvail().y - widget_size.y) * 0.5f};
			break;
		}
		ImGui::SetCursorPos(position);
	};
};
}