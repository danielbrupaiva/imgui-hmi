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
			set_layout_position(m_layout);
			ImGui::Text("%s", get_label().c_str());
		};

		set_font_size();

		_render();

		clean_font();

	};

	inline void set_font_size() const
	{

		if (!Font::isValid(m_font_size)) {
			std::string msg = fmt::format("Font size not available");
			logger.error("{}", msg);
			throw std::invalid_argument(msg);
		}

		if (m_font_size == Font::Size::DEFAULT) {
			return;
		}

		ImGuiIO &io = ImGui::GetIO();
		(void)io;
		ImGui::PushFont(io.Fonts->Fonts[static_cast<int32_t>(m_font_size)]);
	};

	inline void clean_font()
	{
		if (m_font_size == Font::Size::DEFAULT) {
			return;
		}
		ImGui::PopFont();
	}

	inline void set_layout_position(const Layout &layout)
	{
		ImVec2 text_size = ImGui::CalcTextSize(m_label.c_str());

		switch (m_layout) {
			case Layout::NONE: ImGui::SetCursorPos(m_position);
				break;
			case Layout::CENTER: ImGui::SetCursorPos(IWidget::center(text_size));
				break;
			case Layout::TOP:break;
			case Layout::BOTTON:break;
			case Layout::LEFT:break;
			case Layout::RIGHT:break;
		}
	}
};
}