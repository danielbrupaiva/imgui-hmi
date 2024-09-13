//
// Created by daniel on 9/13/24.
//

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
	//FSM definition
	enum class eSystemState
	{
		INVALID = -1, SCREEN1, SCREEN2, SCREEN3, SCREEN4, SCREEN5
	};
private:
	eSystemState m_current_state = eSystemState::INVALID;
	std::vector<std::unique_ptr<App::IScreen>> m_FSM;

public:
	explicit ScreenManager(const eSystemState initial_state, std::vector<std::unique_ptr<App::IScreen>> &fsm)
		: m_current_state(initial_state), m_FSM{std::move(fsm)}
	{
	}

	void render()
	{
		if (!m_FSM.empty()) {
			m_FSM[static_cast<int32_t>(m_current_state)]->render();
		}
	}

	[[nodiscard]] inline eSystemState get_current_state() const
	{
		return m_current_state;
	}
	inline void set_current_state(eSystemState current_state)
	{
		m_current_state = current_state;
	}
};
} // App