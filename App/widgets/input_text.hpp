#pragma once

#include "i_widget.hpp"

namespace App::Widget
{
class InputText: public IWidget
{
public:
	explicit InputText(IMGUI &ui, const std::string_view label, std::string &text)
		: IWidget(ui, label), m_text(text)
	{}

	explicit InputText(IMGUI &ui,
					   const std::string_view label,
					   std::string &text,
					   const Font::Size &font_size = Font::Size::DEFAULT,
					   ImGuiInputTextFlags flags = ImGuiInputTextFlags_None)
		: IWidget(ui, label), m_font_size(font_size), m_text(text), m_flags(flags)
	{}

	virtual void operator()()
	{
		render();
	}

	virtual void operator()(const ImVec2 &size, const ImVec2 &position)
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
		Layout::set_position(m_gravity, m_position, m_size);
		ImGui::InputTextWithHint(fmt::format("##{}", m_label).c_str(), m_hint.c_str(), &m_text, m_flags);
		Font::clean_font(m_font_size);
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
	ImGuiInputTextFlags m_flags = ImGuiInputTextFlags_None;
	std::string m_text;
	std::string m_hint;
};
}