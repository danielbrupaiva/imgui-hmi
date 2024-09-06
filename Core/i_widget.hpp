#pragma once

#include <iostream>
#include "imgui.hpp"

namespace Core
{
class IWidget
{
protected:
	std::string m_label;
	uint32_t m_id = 0;
	int32_t m_width = 0;
	int32_t m_height = 0;
	ImVec2 m_position = ImVec2(0, 0);
	bool m_visible = true;

public:
	explicit IWidget() = default;
	explicit IWidget(const std::string_view label,
					 const int32_t &width,
					 const int32_t &height,
					 const ImVec2 &position)
		: m_label(label), m_width(width), m_height(height), m_position(position)
	{}

public:
	[[nodiscard]] const std::string &get_label()
	{
		return m_label;
	}
	void set_label(const std::string &label)
	{
		m_label = label;
	}
	[[nodiscard]] uint32_t get_id() const
	{
		return m_id;
	}
	void set_id(uint32_t id)
	{
		m_id = id;
	}
	[[nodiscard]] int32_t get_width() const
	{
		return m_width;
	}
	[[nodiscard]] ImVec2 get_size() const
	{
		return {static_cast<float>(m_width), static_cast<float>(m_height)};
	}
	void set_size(const ImVec2 &size)
	{
		m_width = static_cast<int32_t>(std::floor(size.x));
		m_height = static_cast<int32_t>(std::floor(size.y));
	}
	void set_width(const int32_t width)
	{
		m_width = width;
	}
	[[nodiscard]] int32_t get_height() const
	{
		return m_height;
	}
	void set_height(const int32_t height)
	{
		m_height = height;
	}
	[[nodiscard]] const ImVec2 &get_position()
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
};
}