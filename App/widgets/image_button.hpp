#pragma once

#include "i_widget.hpp"
#include "button.hpp"
#include "image.hpp"

namespace App::Widget
{
class ImageButton: public Button
{
public:
	ImageButton(const std::string_view &label,
				const std::string_view filename,
				const std::function<void()> &callback = nullptr)
		: Button(label, callback), m_texture(std::make_unique<Widget::Image>(filename))
	{
		assert(m_texture);
	}

	ImageButton(const std::string_view &label,
				const std::string_view filename,
				const ImVec2 &size,
				const std::function<void()> &callback = nullptr)
		: Button(label, size, callback), m_texture(std::make_unique<Widget::Image>(filename))
	{
		assert(m_texture);
		m_texture->set_size(size);
	}

	bool operator()() override
	{
		render();
		return m_state;
	}

	bool operator()(const ImVec2 &size, const ImVec2 &position) override
	{
		set_size(size);
		set_position(position);
		return operator()();
	}

private:
	void render() override
	{
		Layout::set_layout_position(m_gravity, m_position, get_size());
		if (ImGui::ImageButton(m_texture->ID(), get_size())) {
			if (m_callback) {
				m_callback();
			}
		}
	}

private:
	std::unique_ptr<Widget::Image> m_texture;
};
}