#pragma once

#include <functional>
#include "IMGUI.hpp"
#include "base_widget.hpp"

struct ImVec2;

namespace App::Widget
{
class Button: public BaseWidget
{
public:
	~Button() override = default;

	explicit Button(IMGUI &ui,
			const std::string_view label,
			const ImVec2 &size = ImVec2(),
			Layout::Gravity gravity = Layout::Gravity::NONE,
			const std::vector<StyleColor> & style_colors = {},
			const std::function<void()> &callback = nullptr,
			const bool visible = true)
	: BaseWidget(ui, label, size, ImVec2(), gravity, style_colors, visible), m_callback(callback)
	{}

	explicit Button(IMGUI &ui,
				const std::string_view label,
				const ImVec2 &size = ImVec2(),
				const ImVec2 &position = ImVec2(),
				Layout::Gravity gravity = Layout::Gravity::NONE,
				const std::vector<StyleColor> & style_colors = {},
				const std::function<void()> &callback = nullptr,
				const bool visible = true)
	: BaseWidget(ui, label, size, position, gravity, style_colors, visible), m_callback(callback)
	{}

	virtual void operator()()
	{
		render();
	}

	virtual void operator()(const Layout::Gravity &gravity)
	{
		set_gravity(gravity);
		operator()();
	}

	virtual void operator()(const ImVec2 &size, const ImVec2 &position)
	{
		set_size(size);
		set_position(position);
		operator()();
	}

	[[nodiscard]] inline bool is_clicked() const
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
	[[nodiscard]] inline const std::function<void()> &get_callback() const
	{
		return m_callback;
	}

	inline void set_callback(const std::function<void()> &callback)
	{
		m_callback = callback;
	}

	void render() override
	{
		if (m_visible) {
			UI().layout().set_cursor_position(m_gravity, m_position, m_size);
			if (UI().widgets().Button(m_label, m_size)) {
				if (m_callback)
					m_callback();
			}
		}
	}

private:
	volatile bool m_state = false;
	std::function<void()> m_callback = nullptr;
};
}
