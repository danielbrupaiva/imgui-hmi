#pragma once

#include <iostream>
#include "imgui.hpp"

namespace App
{

class IWidget
{
public:
	IWidget(bool m_visible,
			const ImVec2 &m_position,
			const ImVec2 &m_size,
			const std::string_view m_label,
			uint32_t m_id)
		: m_visible(m_visible), m_position(m_position), m_size(m_size), m_label(m_label), m_id(m_id)
	{}

private:
	uint32_t m_id;
	std::string m_label;
	ImVec2 m_size;
	ImVec2 m_position;
	bool m_visible;

public:
	inline uint32_t get_id() const
	{ return m_id; }
	inline void set_id(uint32_t id)
	{ m_id = id; }
	inline const std::string &get_label() const
	{ return m_label; }
	inline void set_label(const std::string &label)
	{ m_label = label; }
	inline const ImVec2 &get_size() const
	{ return m_size; }
	inline void set_size(const ImVec2 &size)
	{ m_size = size; }
	inline const ImVec2 &get_position() const
	{ return m_position; }
	inline void set_position(const ImVec2 &position)
	{ m_position = position; }
	inline bool is_visible() const
	{ return m_visible; }
	inline void set_visible(bool visible)
	{ m_visible = visible; }
};
} // App