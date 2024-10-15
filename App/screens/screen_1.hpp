#pragma once

#include "i_screen.hpp"
#include "logger.hpp"
#include "widgets.hpp"

namespace App
{
class Screen1: public IScreen
{
public:
	Screen1(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
//		splash_button(Widget::Layout::Gravity::WINDOW_CENTER);
		splash(ImGui::GetContentRegionAvail(), ImGui::GetCursorPos());
	}
private:
	Widget::Image splash{"./resources/morpheus.jpg"};
	Widget::ImageButton splash_button{"splash", "./resources/morpheus.jpg", [&]
	{
		splash_button.toggle_state();
		logger.info("{} state: {}", splash_button.get_label(), splash_button.get_state());
	}};
};
}