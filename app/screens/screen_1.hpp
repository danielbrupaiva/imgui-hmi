#pragma once

#include "i_screen.hpp"
#include "logger.hpp"

namespace App
{
class Screen1: public IScreen
{
public:
	Screen1(IMGUImpl &ui, const std::string_view &title, const ImVec2 &size)
		: IScreen(ui, title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		//		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.173f, 0.173f, 0.173f, 0.0f));
		//		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.271f, 0.271f, 0.271f, 0.0f));
		//		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.173f, 0.173f, 0.173f, 0.0f));
		splash_button(ImGui::GetContentRegionAvail(), ImGui::GetCursorPos());
		//		ImGui::PopStyleColor(3);
		//		splash(ImGui::GetContentRegionAvail(), ImGui::GetCursorPos());
	}

private:
	Widget::Image splash{m_ui, "./resources/morpheus.jpg"};
	Widget::ImageButton splash_button{
		m_ui, "./resources/morpheus.jpg", ILayout::Gravity::CENTER, [&]
		{
			splash_button.toggle_state();
			logger.info("{} state: {}", splash_button.get_label(), splash_button.is_clicked());
		}
	};
};
}
