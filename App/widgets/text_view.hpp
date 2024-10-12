#pragma once

#include "i_widget.hpp"

namespace App::Widget
{
class TextView: public IWidget
{
public:
	explicit TextView(const std::string_view label)
	{
		m_label = label;
	}

	explicit TextView(const std::string_view label, const Font::Size &font_size)
		: m_font_size(font_size)
	{
		m_label = label;
	}

	void operator()()
	{
		render();
	}

	void operator()(const Layout::Position &layout)
	{
		set_layout(layout);
		operator()();
	}

	void operator()(const ImVec2 &position)
	{
		set_position(position);
		operator()();
	}

	void operator()(const std::string &text)
	{
		set_label(text);
		operator()();
	}

	void operator()(const std::string &text, const Font::Size &font_size)
	{
		m_font_size = font_size;
		set_label(text);
		operator()();
	}
	inline void calculate_size()
	{
		// If size not init
		if (get_size().x == 0.0f && get_size().y == 0.0f) {
			set_size(ImGui::CalcTextSize(get_label().c_str()));
		}
		// If default font return
		if (m_font_size == Font::Size::DEFAULT) {
			return;
		}
		// Update size according new font size
		set_size(ImGui::CalcTextSize(get_label().c_str()));
	}

private:
	void render() override
	{
		Font::set_font_size(m_font_size);
		calculate_size();
		Layout::set_layout_position(get_layout(), m_position, get_size());
		ImGui::Text("%s", get_label().c_str());
		Font::clean_font(m_font_size);
	}

private:
	Font::Size m_font_size = Font::Size::DEFAULT;
};
}