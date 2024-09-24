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
	std::function<void()> m_callback = nullptr;

public:
	explicit Button(const std::string_view &label,
					const ImVec2 &size,
					const ImVec2 &position,
					const std::function<void()> &callback = nullptr)
	{
		m_callback = callback;
		set_label(label);
		set_size(size);
		set_position(position);
	}

	virtual bool operator()()
	{
		render();
		return m_state;
	}
private:
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