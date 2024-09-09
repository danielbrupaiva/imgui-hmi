#pragma once

#include <functional>
#include "logger.hpp"
#include "utils.hpp"
#include "widgets/i_widget.hpp"

namespace Core
{
class Button: public IWidget
{
	bool m_state = false;
	static uint32_t m_nextID;
	std::function<void()> m_callback = nullptr;

public:
	Button(const std::string_view &label, const ImVec2 &size, const ImVec2 &position)
		: IWidget(label, static_cast<int32_t>(size.x), static_cast<int32_t>(size.y), position)
	{
		set_id();
	}

	Button(const std::string_view &label,
		   const ImVec2 &size,
		   const ImVec2 &position,
		   bool m_state,
		   const std::function<void()> &m_callback)
		: IWidget(label, static_cast<int32_t>(size.x), static_cast<int32_t>(size.y), position),
		  m_state(m_state),
		  m_callback(m_callback)
	{
		set_id();
	}

	void render()
	{
		if (ImGui::Button(get_label().c_str(), get_size())) {
			TOGGLE(m_state);
			m_callback();
		}
	}

	bool operator()()
	{
		render();
		return m_state;
	}
private:
	void set_id()
	{
		m_id = m_nextID++;
	}

};
}

uint32_t Core::Button::m_nextID = 0;