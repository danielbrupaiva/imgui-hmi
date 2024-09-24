#pragma once

#include "logger.hpp"
#include "i_widget.hpp"

namespace App
{
class TextView: public IWidget
{
	int32_t m_font_size = static_cast<int32_t>(App::IMGUI::FontSize::DEFAULT);

public:
	explicit TextView(const std::string_view text)
	{
		set_label(text);
	}

	explicit TextView(const std::string_view text, const int32_t font_size, const ImVec2 &position)
	{
		set_label(text);
		set_font_size(font_size);
		set_position(position);
	}

	void operator()()
	{
		render();
	}

private:
	void render() override
	{
		set_font_size(m_font_size);
		set_size(ImGui::CalcTextSize(get_label().c_str()));
		set_position(m_position);
		ImGui::Text("%s", get_label().c_str());
		ImGui::PopFont();
	}
public:
	static void set_font_size(int32_t font_size)
	{
		ImGuiIO &io = ImGui::GetIO();
		(void)io;

		if (font_size > io.Fonts->Fonts.size()) {
			std::string msg = fmt::format("Font size not available");
			logger.error("{}", msg);
			throw std::invalid_argument(msg);
		}
		ImGui::PushFont(io.Fonts->Fonts[font_size]);
	}
};
}