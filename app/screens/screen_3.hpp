#pragma once

#include "i_screen.hpp"
#include "logger.hpp"

namespace App
{
class Screen3: public IScreen
{
public:
	Screen3(IMGUImpl &ui, const std::string_view &title, const ImVec2 &size)
		: IScreen(ui, title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		text_view(fmt::format("{}: {}", input_text.get_label(), input_text.get_text()));
		input_text();

		text_view2(fmt::format("{}: {}", input_text2.get_label(), input_text2.get_text()));
		input_text2();
	}

private:
	std::string m_username;
	Widget::InputText input_text{m_ui, "Username", m_username, Font::Size::_36px};
	Widget::TextView text_view{m_ui, "Enter text here", Font::Size::_36px};

	std::string m_password;
	Widget::InputText input_text2{m_ui, "Password", m_password, Font::Size::_36px, ImGuiInputTextFlags_Password};
	Widget::TextView text_view2{m_ui, "Enter text here", Font::Size::_36px};
};
}
