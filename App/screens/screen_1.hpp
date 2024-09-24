#pragma once

#include "i_screen.hpp"
#include "logger.hpp"
#include "image.hpp"

namespace App
{
class Screen1: public IScreen
{
	std::unique_ptr<Image> splash;
public:
	Screen1(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
		splash = std::make_unique<Image>("./resources/morpheus.jpg");
	}
	void render() override
	{
		splash->operator()(ImGui::GetContentRegionAvail(), ImGui::GetCursorPos());
	}
};
}