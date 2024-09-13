//
// Created by daniel on 9/13/24.
//

#pragma once

#include "i_screen.hpp"
#include "logger.hpp"

namespace App
{
class Screen1: public IScreen
{
public:
	Screen1(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{}
	void render() override
	{
		logger.debug("Render call");
	}
};
}