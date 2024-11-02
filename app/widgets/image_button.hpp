#pragma once

#include "base_widget.hpp"
#include "button.hpp"
#include "image.hpp"

namespace App::Widget
{
class ImageButton: public Button
{
public:
	explicit ImageButton(IMGUI &ui,
	                     const std::filesystem::path &&filename,
	                     const ILayout::Gravity &gravity,
	                     const std::function<void()> &callback = nullptr)
		: Button(ui, filename.stem().c_str(), ImVec2(0, 0), callback),
		  m_texture(std::make_unique<Image>(m_ui, filename.c_str()))
	{
		assert(m_texture);
		set_gravity(gravity);
	}

	explicit ImageButton(IMGUI &ui,
	                     const std::filesystem::path &&filename,
	                     const ImVec2 &size = ImVec2(0.0f, 0.0f),
	                     const std::function<void()> &callback = nullptr)
		: Button(ui, filename.stem().c_str(), size, callback),
		  m_texture(std::make_unique<Image>(m_ui, filename.c_str()))
	{
		assert(m_texture);
		m_texture->set_size(size);
	}

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
		UI().layout().set_cursor_position(m_gravity, m_position, m_size);
		if (ImGui::ImageButton(m_label.c_str(), m_texture->ID(), m_size)) {
			if (get_callback()) {
				get_callback().operator()();
			}
		}
	}

private:
	std::unique_ptr<Image> m_texture;
};
}
