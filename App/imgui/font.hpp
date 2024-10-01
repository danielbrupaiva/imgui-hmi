#pragma once
// Emedded font
#include "../resources/fonts/Roboto-Regular.embed"

namespace App::Font
{
enum class Size
{
	DEFAULT = 0, _22px, _24px, _36px, _48px, _60px, _72px
};

static bool isValid(Size font_size)
{
	return font_size >= Size::DEFAULT && font_size <= Size::_72px;
};

static void set_font_size(const Font::Size &font_size)
{
	if (!Font::isValid(font_size)) {
		std::string msg = fmt::format("Font size not available");
		logger.error("{}", msg);
		throw std::invalid_argument(msg);
	}

	if (font_size == Font::Size::DEFAULT) {
		return;
	}

	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	ImGui::PushFont(io.Fonts->Fonts[static_cast<int32_t>(font_size)]);
};

static void clean_font(const Font::Size &font_size)
{
	if (font_size == Font::Size::DEFAULT) {
		return;
	}
	ImGui::PopFont();
}
};