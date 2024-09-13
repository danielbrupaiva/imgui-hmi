#pragma once

#include "i_screen.hpp"
#include "logger.hpp"
#include "image.hpp"

namespace App
{
class Screen1: public IScreen
{
	std::map<std::string, App::Image> m_textures = {
		std::make_pair("splash", Image("./resources/morpheus.jpg"))
	};

public:
	Screen1(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		m_textures["splash"].operator()(ImGui::GetContentRegionAvail(), ImGui::GetCursorPos());
	}
};
}