#pragma once

#include "i_screen.hpp"
#include "logger.hpp"
#include "text_view.hpp"

namespace App
{
class Screen2: public IScreen
{
	TextView text_view1{get_title(), static_cast<int32_t>(App::IMGUI::FontSize::_36px)};

public:
	Screen2(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		text_view1();
		text_view1(IWidget::Layout::CENTER);
	}
};
}