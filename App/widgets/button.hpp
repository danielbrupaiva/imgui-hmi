#pragma once

#include <functional>
#include "logger.hpp"
#include "utils.hpp"
#include "i_widget.hpp"

namespace App
{
class Button: public IWidget
{
	bool m_state = false;
	static uint32_t m_nextID;
	std::function<void()> m_callback = nullptr;

public:
	explicit Button(const std::string_view &label,
					const ImVec2 &size,
					const ImVec2 &position,
					bool m_state = false,
					const std::function<void()> &m_callback = nullptr)
		: IWidget(label, static_cast<int32_t>(size.x), static_cast<int32_t>(size.y), position),
		  m_state(m_state),
		  m_callback(m_callback)
	{
		m_id = m_nextID++;
	}

	bool operator()()
	{
		render();
		return m_state;
	}

	void render() override
	{
		if (ImGui::Button(get_label().c_str(), get_size())) {
			toggle_state();
			m_callback();
		}
	}

public:
	[[nodiscard]] inline bool get_state() const
	{
		return m_state;
	}

	inline void set_state(bool state)
	{
		m_state = state;
	}

	inline void toggle_state()
	{
		m_state = !m_state;
	}

};
}

uint32_t App::Button::m_nextID = 0;