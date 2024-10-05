#pragma once

#include "i_screen.hpp"
#include "logger.hpp"
#include "widgets.hpp"

namespace App
{
class Screen4: public IScreen
{
public:
	Screen4(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		text_view(Widget::Layout::Position::WINDOW_CENTER);
	}
private:
	Widget::TextView text_view{get_title(), Font::Size::_36px};

};
}