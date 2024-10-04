#pragma once

#include "i_screen.hpp"
#include "logger.hpp"

namespace App
{
class Screen3: public IScreen
{
	std::string username;
	std::string password;
public:
	Screen3(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		auto font = Font::Size::_36px;
		Font::set_font_size(font);
		Widget::TextView(fmt::format("Username: {}", username));
		Widget::InputText("##username", username, "Username");
		Widget::TextView("Password:");
		Widget::InputText("##password", password, "Password", false);
		Font::clean_font(font);
	}
};
}