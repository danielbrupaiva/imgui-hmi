#pragma once

#include "logger.hpp"
#include "i_widget.hpp"

namespace App
{
class TextInput: public IWidget
{
public:
	TextInput(const std::string_view &label, const ImVec2 &size, const ImVec2 &position)
		: IWidget(label, size, position)
	{
		throw std::runtime_error("Not implemented");
	}

};
}