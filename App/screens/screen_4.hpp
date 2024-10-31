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
	Screen4(IMGUImpl &ui, const std::string_view &title, const ImVec2 &size)
		: IScreen(ui, title, size)
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

	Widget::Image icon{m_ui, "./resources/profile.png"};

	Widget::Button btn0{m_ui, "btn0", ImVec2(80.0f, 80.0f), [&]
	{
		btn0.toggle_state();
		logger.info("{} state: {}", btn0.get_label(), btn0.is_clicked());
	}};

	Widget::Button btn1{m_ui, "btn1", ImVec2(80.0f, 80.0f), [&]
	{
		btn1.toggle_state();
		logger.info("{} state: {}", btn1.get_label(), btn1.is_clicked());
	}};

	Widget::ImageButton image_button{m_ui, "./resources/profile.png", ImVec2(72.0f, 72.0f), [&]
	{
		image_button.toggle_state();
		logger.info("{} state: {}", image_button.get_label(), image_button.is_clicked());
	}};
};
}