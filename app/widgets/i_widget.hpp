#pragma once

#include "IMGUI.hpp"
#include "layout.hpp"
#include "logger.hpp"

namespace App
{
class IWidget
{
public:
	virtual ~IWidget() = default;
	explicit IWidget(IMGUI &ui)
		: m_ui(ui)
	{
	}

	explicit IWidget(IMGUI &ui,
	                 const std::string_view label,
	                 const ImVec2 &size = ImVec2(0, 0),
	                 const ImVec2 &position = ImVec2(0, 0))
		: m_ui(ui), m_label(label), m_size(size), m_position(position)
	{
	}

	virtual void render() = 0;

	[[nodiscard]] inline std::string &get_label()
	{
		return m_label;
	}
	inline void set_label(const std::string_view label)
	{
		m_label = label;
	}
	[[nodiscard]] inline uint32_t ID() const
	{
		return m_id;
	}
	inline void set_id(uint32_t id)
	{
		m_id = id;
	}
	[[nodiscard]] inline float get_width() const
	{
		return m_size.x;
	}
	[[nodiscard]] inline ImVec2 get_size() const
	{
		return m_size;
	}
	inline void set_size(const ImVec2 &size)
	{
		m_size = size;
	}
	[[nodiscard]] inline float get_height() const
	{
		return m_size.y;
	}
	[[nodiscard]] inline const ImVec2 &get_position()
	{
		return m_position;
	}
	inline void set_position(const ImVec2 &position)
	{
		m_position = position;
	}
	[[nodiscard]] inline bool is_visible() const
	{
		return m_visible;
	}
	inline void set_visible(bool visible)
	{
		m_visible = visible;
	}
	[[nodiscard]] inline Widget::Layout::Gravity get_layout() const
	{
		return m_gravity;
	}
	inline void set_gravity(const Widget::Layout::Gravity &gravity)
	{
		m_gravity = gravity;
	}

	[[nodiscard]] inline IMGUI &ui()
	{
		return m_ui;
	}

protected:
	App::IMGUI &m_ui;
	std::string m_label;
	uint32_t m_id = 0;
	ImVec2 m_size = ImVec2(0.0f, 0.0f);
	ImVec2 m_position = ImVec2(0.0f, 0.0f);
	bool m_visible = true;
	Widget::Layout::Gravity m_gravity = Widget::Layout::Gravity::NONE;
};
}
