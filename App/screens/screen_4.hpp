#pragma once

#include "i_screen.hpp"
#include "logger.hpp"
#include "widgets.hpp"
#include "layout.hpp"

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
		btn0();
		btn1();
		image_button();
	}
private:

	Widget::Image icon{"./resources/profile.png"};

	Widget::Button btn0{"btn0", ImVec2(80.0f, 80.0f), [&]
	{
		btn0.toggle_state();
		logger.info("{} state: {}", btn0.get_label(), btn0.get_state());
	}};

	Widget::Button btn1{"btn1", ImVec2(80.0f, 80.0f), [&]
	{
		btn1.toggle_state();
		logger.info("{} state: {}", btn1.get_label(), btn1.get_state());
	}};

	Widget::ImageButton image_button{"imgBtn0", "./resources/profile.png", ImVec2(72.0f, 72.0f), [&]
	{
		image_button.toggle_state();
		logger.info("{} state: {}", image_button.get_label(), image_button.get_state());
	}};
};
}