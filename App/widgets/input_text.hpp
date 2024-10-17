#pragma once

#include "i_widget.hpp"

namespace App::Widget
{
class InputText: public IWidget
{
public:
	explicit InputText(const std::string_view label, std::string &text)
		: m_text(text)
	{
		m_label = label;
	}

	explicit InputText(const std::string_view label,
					   std::string &text,
					   const Font::Size &font_size = Font::Size::DEFAULT,
					   ImGuiInputTextFlags flags = ImGuiInputTextFlags_None)
		: m_font_size(font_size), m_text(text), m_flags(flags)
	{
		m_label = label;
	}

	virtual void operator()()
	{
		render();
	}

	virtual bool operator()(const ImVec2 &size, const ImVec2 &position)
	{
		set_size(size);
		set_position(position);
		operator()();
	}

	[[nodiscard]] inline const std::string &get_text() const
	{
		return m_text;
	}

private:
	void render() override
	{
		Font::set_font_size(m_font_size);
		calculate_size();
		Layout::set_position(get_layout(), m_position, get_size());
		ImGui::InputTextWithHint(fmt::format("##{}", m_label).c_str(), m_hint.c_str(), &m_text, m_flags);
		Font::clean_font(m_font_size);
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
	Font::Size m_font_size = Font::Size::DEFAULT;
	ImGuiInputTextFlags m_flags = ImGuiInputTextFlags_None;
	std::string m_text;
	std::string m_hint;
};
}