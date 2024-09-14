#pragma once

#include "i_screen.hpp"
#include "logger.hpp"

namespace App
{
class Screen2: public IScreen
{
public:
	Screen2(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		ImGuiIO &io = ImGui::GetIO();
		(void)io;
		ImGui::PushFont(io.Fonts->Fonts[3]);
		std::string text = fmt::format("{}", get_title());
		ImVec2 text_size = ImGui::CalcTextSize(text.c_str());
		ImGui::SetCursorPos({(ImGui::GetWindowSize().x - text_size.x) * 0.5f,
							 (ImGui::GetWindowSize().y - text_size.y) * 0.5f});
		ImGui::Text("%s", text.c_str());
		ImGui::PopFont();
	}
};
}