//
// Created by daniel on 9/13/24.
//

#pragma once

#include <vector>
#include <memory>

#include "imgui.hpp"
#include "screen_1.hpp"

namespace App
{
class FSM
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
	explicit FSM(eSystemState initial_state)
		: m_current_state(initial_state)
	{
		m_FSM.push_back(std::make_unique<App::Screen1>("Screen1", ImVec2(1280, 720)));
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