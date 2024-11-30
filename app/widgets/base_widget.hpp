#pragma once

#include "IMGUI.hpp"
#include "style_color.hpp"
#include "logger.hpp"
#include <algorithm>

namespace App::Widget
{
class BaseWidget
{
public:
	virtual ~BaseWidget() = default;

	explicit BaseWidget(IMGUI &ui,
		const std::string_view label,
		const ImVec2 &size = ImVec2(),
		const ImVec2 &position = ImVec2(),
		Layout::Gravity gravity = Layout::Gravity::NONE,
		const std::vector<StyleColor> & style_colors = {},
		bool visible = true)
	: m_ui(ui), m_label(label), m_size(size), m_position(position), m_gravity(gravity), m_style_colors(style_colors), m_visible(visible)
	{}

	virtual void render() = 0;

	virtual void init_render()
	{
		std::ranges::for_each(m_style_colors, [](const StyleColor &style)
		{
			ImGui::PushStyleColor(style.idx, style.col);
		});
	}

	virtual void clear_render()
	{
		ImGui::PopStyleColor(static_cast<int32_t>(m_style_colors.size()));
	}

	void set_custom_styles(const std::vector<StyleColor> &style_colors)
	{
		this->m_style_colors = style_colors;
	}

	[[nodiscard]] std::string &get_label()
	{
		return m_label;
	}
	void set_label(const std::string_view label)
	{
		m_label = label;
	}
	[[nodiscard]] uint32_t ID() const
	{
		return m_id;
	}
	void set_id(uint32_t id)
	{
		m_id = id;
	}
	[[nodiscard]] float get_width() const
	{
		return m_size.x;
	}
	[[nodiscard]] ImVec2 get_size() const
	{
		return m_size;
	}
	void set_size(const ImVec2 &size)
	{
		m_size = size;
	}
	[[nodiscard]] float get_height() const
	{
		return m_size.y;
	}
	[[nodiscard]] const ImVec2 &get_position() const
	{
		return m_position;
	}
	void set_position(const ImVec2 &position)
	{
		m_position = position;
	}
	[[nodiscard]] bool is_visible() const
	{
		return m_visible;
	}
	void set_visible(bool visible)
	{
		m_visible = visible;
	}
	[[nodiscard]] Layout::Gravity get_layout() const
	{
		return m_gravity;
	}
	void set_gravity(const Layout::Gravity &gravity)
	{
		m_gravity = gravity;
	}

	[[nodiscard]] IMGUI &UI()
	{
		return m_ui;
	}

protected:
	IMGUI &m_ui;
	std::string m_label;
	uint32_t m_id = 0;
	ImVec2 m_size = ImVec2(0.0f, 0.0f);
	ImVec2 m_position = ImVec2(0.0f, 0.0f);
	volatile bool m_visible = true;
	Layout::Gravity m_gravity = Layout::Gravity::NONE;
	std::vector<StyleColor> m_style_colors;
};
}
