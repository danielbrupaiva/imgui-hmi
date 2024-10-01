#pragma once

#include "i_screen.hpp"
#include "logger.hpp"
#include "text_view.hpp"

namespace App
{
class Screen2: public IScreen
{
	TextView text_view1{"NONE", Font::Size::_36px};
	TextView text_view2{"CENTER", Font::Size::_36px};
	TextView text_view3{"TOP", Font::Size::_36px};
	TextView text_view4{"BOTTON", Font::Size::_36px};
	TextView text_view5{"LEFT", Font::Size::_36px};
	TextView text_view6{"RIGHT", Font::Size::_36px};

public:
	Screen2(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		text_view1(Layout::NONE);
		text_view2(Layout::WINDOW_CENTER);
		text_view3(Layout::WINDOW_TOP);
		text_view4(Layout::WINDOW_BOTTON);
		text_view5(Layout::WINDOW_LEFT);
		text_view6(Layout::WINDOW_RIGHT);
	}
};
}