#pragma once

#include "i_screen.hpp"
#include "logger.hpp"
#include "input_text.hpp"

namespace App
{
class Screen3: public IScreen
{
public:
	Screen3(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		text_view(input_text.get_text());
		input_text();
	}
private:
	Widget::InputText input_text{"Username", m_username};
	Widget::TextView text_view{"", Font::Size::_36px};
	std::string m_username;
};
}