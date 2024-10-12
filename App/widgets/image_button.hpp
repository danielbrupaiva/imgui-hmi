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
				const ImVec2 &size,
				const ImVec2 &position = ImVec2(0, 0),
				const std::function<void()> &callback = nullptr)
		: Button(label, size, position, callback), m_texture(std::make_unique<Widget::Image>(filename))
	{
		assert(m_texture);
		m_texture->set_size(size);
	}

	bool operator()() override
	{
		render();
		return get_state();
	}

	bool operator()(const ImVec2 &position)
	{
		set_position(position);
		operator()();
		return get_state();
	}
private:
	void render() override
	{
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