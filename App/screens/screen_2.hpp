#pragma once

#include "i_screen.hpp"
#include "logger.hpp"
#include "text_view.hpp"

namespace App
{
class Screen2: public IScreen
{
	std::unique_ptr<TextView> text_view;

public:
	Screen2(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
		text_view = std::make_unique<TextView>("SCREEN 2");
	}
	void render() override
	{
		text_view->operator()();
	}
};
}