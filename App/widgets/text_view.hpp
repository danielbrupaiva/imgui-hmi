#pragma once

#include "logger.hpp"
#include "i_widget.hpp"

namespace App
{
class TextView: public IWidget
{
	Font::Size m_font_size = Font::Size::DEFAULT;

public:
	explicit TextView(const std::string_view text,
					  const Font::Size &font_size = Font::Size::DEFAULT,
					  const ImVec2 &position = ImVec2(0.0f, 0.0f),
					  const Layout &layout = Layout::NONE)
		: m_font_size(font_size)
	{
		m_label = text;
		m_position = position;
		m_layout = layout;
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
		set_font_size(m_font_size);
		set_layout_position(m_layout);
		ImGui::Text("%s", get_label().c_str());
		clean_font(m_font_size);
	};

	inline void set_font_size(const Font::Size &size)
	{
		if (!Font::isValid(size)) {
			std::string msg = fmt::format("Font size not available");
			logger.error("{}", msg);
			throw std::invalid_argument(msg);
		}

		if (m_font_size != Font::Size::DEFAULT) {

			ImGuiIO &io = ImGui::GetIO();
			(void)io;
			ImGui::PushFont(io.Fonts->Fonts[static_cast<int32_t>(m_font_size)]);
			//update widget size
			set_size(ImGui::CalcTextSize(m_label.c_str()));

		}

		if (get_size().x == 0.0f && get_size().y == 0.0f) {
			set_size(ImGui::CalcTextSize(m_label.c_str()));
		}

	};

	inline void clean_font(const Font::Size &size)
	{
		if (size == Font::Size::DEFAULT) {
			return;
		}
		ImGui::PopFont();
	}
};
}