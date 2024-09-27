//
// Created by daniel on 9/27/24.
//

#ifndef FONT_HPP
#define FONT_HPP

// Emedded font
#include "../resources/fonts/Roboto-Regular.embed"

namespace App
{

class Font
{
public:
	enum class Size
	{
		DEFAULT = 0, _22px, _24px, _36px, _48px, _60px, _96px
	};

	static bool isValid(Size font_size)
	{
		return font_size >= Size::DEFAULT && font_size <= Size::_96px;
	};
};

} // App

#endif //FONT_HPP
