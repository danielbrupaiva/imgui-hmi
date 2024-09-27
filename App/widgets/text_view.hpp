#pragma once

#include "logger.hpp"
#include "i_widget.hpp"

namespace App
{
class TextView: public IWidget
{
	Font::Size m_font_size = Font::Size::DEFAULT;
	Layout m_layout = Layout::NONE;

public:
	explicit TextView(const std::string_view text,
					  const Font::Size &font_size = Font::Size::DEFAULT,
					  const ImVec2 &position = ImVec2(0.0f, 0.0f))
		: m_font_size(font_size)
	{
		m_label = text;
		m_position = position;
	}

	void operator()()
	{
		render();
	}
	void operator()(std::string_view text)
	{
		m_label = text;
		operator()();
	}

	void operator()(const ImVec2 &position)
	{
		m_position = position;
		operator()();
	}

	void operator()(const Layout layout)
	{
		m_layout = layout;
		operator()();
	}

	void operator()(std::string_view text, const ImVec2 &position)
	{
		m_label = text;
		m_position = position;
		operator()();
	}

private:
	void render() override
	{
		auto _render = [&]
		{
			ImVec2 text_size = ImGui::CalcTextSize(m_label.c_str());
			set_position(IWidget::center(text_size));
			ImGui::SetCursorPos(get_position());
			ImGui::Text("%s", get_label().c_str());
		};

		if (m_font_size == static_cast<int32_t>(App::IMGUI::FontSize::DEFAULT)) {
			_render();
		}
		else {
			ImGuiIO &io = ImGui::GetIO();
			(void)io;

			if (m_font_size < 0 || m_font_size > io.Fonts->Fonts.size()) {
				std::string msg = fmt::format("Font size not available");
				logger.error("{}", msg);
				throw std::invalid_argument(msg);
			}

			ImGui::PushFont(io.Fonts->Fonts[m_font_size]);


			_render();

			ImGui::PopFont();

		}
	};

	inline void set_font_size(int32_t font_size)
	{
		m_font_size = font_size;
	};
};
}