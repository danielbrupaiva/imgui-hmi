#pragma once

#include <iostream>
#include "imgui.hpp"
#include "logger.hpp"

namespace App
{
class IScreen
{
public:
	explicit IScreen(IMGUI &ui, const std::string_view title, const ImVec2 &size)
		: m_ui(ui), m_title(title), m_size(size)
	{
		m_id = m_nextID++;
		assert(ImGui::GetCurrentContext());
	}
	virtual void render() = 0;

public:
	[[nodiscard]] inline uint32_t get_id() const
	{ return m_id; }
	inline void set_id(uint32_t id)
	{ m_id = id; }
	[[nodiscard]] inline const std::string &get_title() const
	{ return m_title; }
	inline void set_title(const std::string &title)
	{ m_title = title; }
	[[nodiscard]] inline const ImVec2 &get_size() const
	{ return m_size; }
	inline void set_size(const ImVec2 &size)
	{ m_size = size; }

protected:
	App::IMGUI &m_ui;
	uint32_t m_id;
	static uint32_t m_nextID;
	std::string m_title;
	ImVec2 m_size;
};

} // App

uint32_t App::IScreen::m_nextID = 0;