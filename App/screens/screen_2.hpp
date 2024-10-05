#pragma once

#include "i_screen.hpp"
#include "logger.hpp"
#include "text_view.hpp"

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
		text_view1();
		text_view2(Widget::Layout::Position::WINDOW_CENTER);
		text_view3(Widget::Layout::Position::WINDOW_LEFT);
		text_view4(Widget::Layout::Position::WINDOW_RIGHT);
		text_view5(Widget::Layout::Position::WINDOW_TOP);
		text_view6(Widget::Layout::Position::WINDOW_BOTTON);
	}
private:
	Widget::TextView text_view1{get_title()};
	Widget::TextView text_view2{get_title(), Font::Size::_36px};
	Widget::TextView text_view3{get_title(), Font::Size::_36px};
	Widget::TextView text_view4{get_title(), Font::Size::_36px};
	Widget::TextView text_view5{get_title(), Font::Size::_36px};
	Widget::TextView text_view6{get_title(), Font::Size::_36px};
};
}