#pragma once

#include <iostream>
#include "imgui.hpp"
#include "logger.hpp"

namespace App
{
class IScreen
{
	uint32_t m_id;
	static uint32_t m_nextID;
	std::string m_title;
	ImVec2 m_size;

public:
	explicit IScreen(const std::string_view title, const ImVec2 &size)
		: m_title(title), m_size(size)
	{
		assert(get_imgui_context());
		m_id = m_nextID++;
	}
	virtual void render() = 0;

private:
	[[nodiscard]] static ImGuiContext *get_imgui_context()
	{
		ImGuiContext *context = ImGui::GetCurrentContext();
		if (context == nullptr) {
			std::string msg = "No current imgui context";
			logger.error("{}", msg);
			throw std::runtime_error(msg);
		}
		return context;
	}
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
};

} // App

uint32_t App::IScreen::m_nextID = 0;