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
		btn0();
		ImGui::SameLine();
		btn1();
	}
private:

	Widget::Button btn0{"btn0", [&]
	{
		btn0.toggle_state();
		logger.info("{} state: {}", btn0.get_label(), btn0.get_state());
	}};

	Widget::Button btn1{"btn1", [&]
	{
		btn1.toggle_state();
		logger.info("{} state: {}", btn1.get_label(), btn1.get_state());
	}};
};
}