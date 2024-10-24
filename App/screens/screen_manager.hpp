#pragma once

#include <vector>
#include <memory>

#include "logger.hpp"
#include "imgui.hpp"
#include "screen_1.hpp"
#include "screen_2.hpp"
#include "screen_3.hpp"
#include "screen_4.hpp"
#include "screen_5.hpp"

namespace App
{
class ScreenManager
{
	const static uint8_t NUM_SCREENS = 5U;
public:
	enum class eState
	{
		INVALID = -1, SCREEN1, SCREEN2, SCREEN3, SCREEN4, SCREEN5
	};

public:
	//TODO: Improve constructor
	explicit ScreenManager(IMGUI &ui, const eState initial_state)
		: m_ui(ui), m_current_state(initial_state)
	{
		m_screens.reserve(NUM_SCREENS);
		m_screens.emplace_back(std::make_unique<App::Screen1>(m_ui, "Screen1", m_ui.get_spec()->window_size));
		m_screens.emplace_back(std::make_unique<App::Screen2>(m_ui, "Screen2", m_ui.get_spec()->window_size));
		m_screens.emplace_back(std::make_unique<App::Screen3>(m_ui, "Screen3", m_ui.get_spec()->window_size));
		m_screens.emplace_back(std::make_unique<App::Screen4>(m_ui, "Screen4", m_ui.get_spec()->window_size));
		m_screens.emplace_back(std::make_unique<App::Screen5>(m_ui, "Screen5", m_ui.get_spec()->window_size));
	};

	void render()
	{
		if (m_screens.empty()) {
			logger.error("No screen available to render");
			throw std::runtime_error("No screen available to render");
		}
		else {
			m_screens[static_cast<int32_t>(m_current_state)]->render();
		}
	}

	[[nodiscard]] inline eState get_current_state() const
	{
		return m_current_state;
	}
	inline void set_current_state(eState current_state)
	{
		m_current_state = current_state;
	}

private:
	IMGUI &m_ui;
	volatile eState m_current_state = eState::INVALID;
	std::vector<std::unique_ptr<App::IScreen>> m_screens;
};
} // App