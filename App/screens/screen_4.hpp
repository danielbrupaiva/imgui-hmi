#pragma once

#include "i_screen.hpp"
#include "logger.hpp"

namespace App
{
class Screen4: public IScreen
{
public:
	Screen4(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{}
	void render() override
	{
		logger.debug("Render {}", get_title());
	}
};
}