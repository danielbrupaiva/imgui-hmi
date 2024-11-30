#pragma once

#include "base_widget.hpp"
#include "button.hpp"
#include "image.hpp"

namespace App::Widget
{
class ImageButton: public Button
{
public:
	~ImageButton() override = default;
	explicit ImageButton(IMGUI &ui,
			const std::filesystem::path &&filename,
			Layout::Gravity gravity = Layout::Gravity::NONE,
			const std::vector<StyleColor> & style_colors = {},
			const std::function<void()> &callback = nullptr,
			const bool state = false,
			const bool visible = true)
	: Button(ui, filename.stem().c_str(), ImVec2(), ImVec2(), gravity, style_colors, callback, visible),
		m_texture(std::make_unique<Image>(m_ui, filename.c_str()))
	{}

	explicit ImageButton(IMGUI &ui,
				const std::filesystem::path &&filename,
				const ImVec2 &size = ImVec2(),
				const ImVec2 &position = ImVec2(),
				Layout::Gravity gravity = Layout::Gravity::NONE,
				const std::vector<StyleColor> & style_colors = {},
				const std::function<void()> &callback = nullptr,
				const bool visible = true)
	: Button(ui, filename.stem().c_str(), size, position, gravity, style_colors, callback, visible),
		m_texture(std::make_unique<Image>(m_ui, filename.c_str()))
	{}

	void operator()() override
	{
		render();
	}

	void operator()(const ILayout::Gravity &gravity) override
	{
		set_gravity(gravity);
		operator()();
	}

	void operator()(const ImVec2 &size, const ImVec2 &position) override
	{
		m_texture->resize(size);
		set_size(m_texture->get_size());
		set_position(position);
		operator()();
	}

private:
	void render() override
	{
		if (m_visible) {
			//Init render
			init_render();
			UI().layout().set_cursor_position(m_gravity, m_position, m_size);
			//Render
			if (ImGui::ImageButton(m_label.c_str(), m_texture->ID(), m_size)) {
				if (get_callback()) {
					get_callback().operator()();
				}
			}
			//Clear render
			clear_render();
		}
	}

private:
	std::unique_ptr<Image> m_texture;
};
}
