#pragma once

#include "i_screen.hpp"
#include "logger.hpp"
#include "text_view.hpp"

namespace App
{
class Screen2: public IScreen
{
	TextView text_view{get_title(), Font::Size::_36px};

public:
	Screen2(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		text_view(IWidget::Layout::CENTER);
	}
};
}