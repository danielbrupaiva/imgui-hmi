#pragma once

#include "i_screen.hpp"
#include "widgets.hpp"
#include "logger.hpp"

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
		App::Widget::TextView(get_title(), Font::Size::_36px, Widget::Layout::Position::WINDOW_CENTER);
	}
};
}