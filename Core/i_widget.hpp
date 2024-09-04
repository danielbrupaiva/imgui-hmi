#pragma once

#include <iostream>
#include "imgui.hpp"

namespace Core
{
class IWidget
{
private:
	std::string m_label;
	int32_t m_id = 0;
	ImVec2 m_size = ImVec2(0, 0);
	ImVec2 m_position = ImVec2(0, 0);
	bool m_visible = true;

public:
	explicit IWidget() = default;
	explicit IWidget(const std::string_view label,
					 const ImVec2 &size,
					 const ImVec2 &position)
		: m_label(label), m_size(size), m_position(position)
	{}

public:
	const std::string &get_label() const
	{
		return m_label;
	}
	void set_label(const std::string &label)
	{
		m_label = label;
	}
	uint32_t get_id() const
	{
		return m_id;
	}
	void set_id(int32_t id)
	{
		m_id = id;
	}
	const float get_width() const
	{
		return m_size.x;
	}
	void set_width(const float width)
	{
		m_size.x = width;
	}
	const float get_height() const
	{
		return m_size.y;
	}
	void set_height(const float height)
	{
		m_size.y = height;
	}
	const ImVec2 &get_size() const
	{
		return m_size;
	}
	void set_size(const ImVec2 &size)
	{
		m_size = size;
	}
	const ImVec2 &get_position() const
	{
		return m_position;
	}
	void set_position(const ImVec2 &position)
	{
		m_position = position;
	}
	bool is_visible() const
	{
		return m_visible;
	}
	void set_visible(bool visible)
	{
		m_visible = visible;
	}
};
}