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
	[[nodiscard]] const std::string &get_label() const
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
	[[nodiscard]] virtual int32_t get_width() const
	{
		return m_width;
	}
	void virtual set_width(const int32_t width)
	{
		m_width = width;
	}
	[[nodiscard]] virtual int32_t get_height() const
	{
		return m_height;
	}
	void virtual set_height(const int32_t height)
	{
		m_height = height;
	}
	[[nodiscard]] virtual const ImVec2 &get_position() const
	{
		return m_position;
	}
	void virtual set_position(const ImVec2 &position)
	{
		m_position = position;
	}
	[[nodiscard]] virtual bool is_visible() const
	{
		return m_visible;
	}
	virtual void set_visible(bool visible)
	{
		m_visible = visible;
	}
};
}