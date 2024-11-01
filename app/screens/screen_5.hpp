#pragma once

#include "i_screen.hpp"
#include "logger.hpp"

namespace App
{
class Screen5: public IScreen
{
public:
	Screen5(IMGUImpl &ui, const std::string_view &title, const ImVec2 &size)
		: IScreen(ui, title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		text_view(Widget::Layout::Gravity::WINDOW_CENTER);
	}
private:
	Widget::TextView text_view{m_ui, get_title(), Font::Size::_36px};
};
}