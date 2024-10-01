#pragma once

#include "i_screen.hpp"
#include "logger.hpp"

namespace App
{
class Screen2: public IScreen
{
public:
	Screen2(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		Widget::TextView("NONE", Font::Size::_36px, Widget::Layout::Position::NONE);
		Widget::TextView("CENTER", Font::Size::_36px, Widget::Layout::Position::WINDOW_CENTER);
		Widget::TextView("TOP", Font::Size::_36px, Widget::Layout::Position::WINDOW_TOP);
		Widget::TextView("BOTTON", Font::Size::_36px, Widget::Layout::Position::WINDOW_BOTTON);
		Widget::TextView("LEFT", Font::Size::_36px, Widget::Layout::Position::WINDOW_LEFT);
		Widget::TextView("RIGHT", Font::Size::_36px, Widget::Layout::Position::WINDOW_RIGHT);

		Widget::TextView("Text input:", Font::Size::_36px, Widget::Layout::Position::NONE, ImVec2(200, 100));
	}
};
}