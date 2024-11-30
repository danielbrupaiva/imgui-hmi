#pragma once

#include "base_widget.hpp"

namespace App::Widget
{
class TextView: public BaseWidget
{
public:
	explicit TextView(IMGUI &ui, const std::string_view label)
		: BaseWidget(ui, label)
	{}

	explicit TextView(IMGUI &ui, const std::string_view label, const Font::Size &font_size)
		: BaseWidget(ui, label), m_font_size(font_size)
	{}

	virtual void operator()()
	{
		render();
	}

	virtual void operator()(const ILayout::Gravity &layout)
	{
		set_gravity(layout);
		operator()();
	}

	virtual void operator()(const ImVec2 &position)
	{
		set_position(position);
		operator()();
	}

	virtual void operator()(const std::string &text)
	{
		set_label(text);
		operator()();
	}

	virtual void operator()(const std::string &text, const Font::Size &font_size)
	{
		m_font_size = font_size;
		set_label(text);
		operator()();
	}

private:
	void render() override
	{
		if (m_visible) {
			Font::set_font_size(m_font_size);
			calculate_size();
			UI().layout().set_cursor_position(m_gravity, m_position, m_size);
			ImGui::Text("%s", m_label.c_str());
			Font::clean_font(m_font_size);
		}
	}

	inline void calculate_size()
	{
		// If size not init
		if (m_size.x == 0.0f && m_size.y == 0.0f) {
			set_size(ImGui::CalcTextSize(m_label.c_str()));
		}
		// If default font return
		if (m_font_size == Font::Size::DEFAULT) {
			return;
		}
		// Update size according new font size
		set_size(ImGui::CalcTextSize(m_label.c_str()));
	}

private:
	Font::Size m_font_size = Font::Size::DEFAULT;
};
}