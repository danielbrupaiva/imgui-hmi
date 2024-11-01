#pragma once
#include "logger.hpp"
// Embedded font
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

static void init(ImGuiIO &io)
{
	// Load default font
	ImFontConfig fontConfig;
	fontConfig.FontDataOwnedByAtlas = false;
	ImFont *robotoFont22px =
		io.Fonts->AddFontFromMemoryTTF((void *)g_RobotoRegular, sizeof(g_RobotoRegular), 22.0f, &fontConfig);
	ImFont *robotoFont24px =
		io.Fonts->AddFontFromMemoryTTF((void *)g_RobotoRegular, sizeof(g_RobotoRegular), 24.0f, &fontConfig);
	ImFont *robotoFont36px =
		io.Fonts->AddFontFromMemoryTTF((void *)g_RobotoRegular, sizeof(g_RobotoRegular), 36.0f, &fontConfig);
	ImFont *robotoFont48px =
		io.Fonts->AddFontFromMemoryTTF((void *)g_RobotoRegular, sizeof(g_RobotoRegular), 48.0f, &fontConfig);
	ImFont *robotoFont60px =
		io.Fonts->AddFontFromMemoryTTF((void *)g_RobotoRegular, sizeof(g_RobotoRegular), 60.0f, &fontConfig);
	ImFont *robotoFont72px =
		io.Fonts->AddFontFromMemoryTTF((void *)g_RobotoRegular, sizeof(g_RobotoRegular), 72.0f, &fontConfig);

	io.FontDefault = robotoFont22px;
}

};