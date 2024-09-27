#pragma once

#include "i_screen.hpp"
#include "logger.hpp"
#include "image.hpp"

namespace App
{
class Screen1: public IScreen
{
	Image splash{"./resources/morpheus.jpg"};
public:
	Screen1(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		splash(ImGui::GetContentRegionAvail(), ImGui::GetCursorPos());
	}
};
}