#pragma once

#include <iostream>
#include "imgui.hpp"

namespace App
{

class IScreen
{
public:
	IScreen(uint32_t id, const std::string &title, const ImVec2 &size)
		: m_id(id), m_title(title), m_size(size)
	{}
	virtual void render() = 0;

private:
	uint32_t m_id;
	std::string m_title;
	ImVec2 m_size;

public:
	inline uint32_t get_id() const
	{ return m_id; }
	inline void set_id(uint32_t id)
	{ m_id = id; }
	inline const std::string &get_title() const
	{ return m_title; }
	inline void set_title(const std::string &title)
	{ m_title = title; }
	inline const ImVec2 &get_size() const
	{ return m_size; }
	inline void set_size(const ImVec2 &size)
	{ m_size = size; }
};

} // App