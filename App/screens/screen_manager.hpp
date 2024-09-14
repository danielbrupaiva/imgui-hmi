#pragma once

#include <vector>
#include <memory>

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
public:
	enum class eState
	{
		INVALID = -1, SCREEN1, SCREEN2, SCREEN3, SCREEN4, SCREEN5
	};
private:
	volatile eState m_current_state = eState::INVALID;
	std::vector<std::unique_ptr<App::IScreen>> m_screens;

public:
	//TODO: Improve constructor
	explicit ScreenManager(IMGUI &ui, const eState initial_state)
		: m_current_state(initial_state)
	{
		m_screens.push_back(std::make_unique<App::Screen1>("Screen1", ui.get_spec()->window_size));
		m_screens.push_back(std::make_unique<App::Screen2>("Screen2", ui.get_spec()->window_size));
		m_screens.push_back(std::make_unique<App::Screen3>("Screen3", ui.get_spec()->window_size));
		m_screens.push_back(std::make_unique<App::Screen4>("Screen4", ui.get_spec()->window_size));
		m_screens.push_back(std::make_unique<App::Screen5>("Screen5", ui.get_spec()->window_size));
	};

	explicit ScreenManager(const eState initial_state, std::vector<std::unique_ptr<App::IScreen>> &screens)
		: m_current_state(initial_state), m_screens{std::move(screens)}
	{}

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
};
} // App