#pragma once

namespace App
{
class Screen2: public IScreen
{
public:
	Screen2(IMGUImpl &ui, const std::string_view &title, const ImVec2 &size)
		: IScreen(ui, title, size)
	{
		logger.debug("Constructor {}", get_title());
	}
	void render() override
	{
		text_view1();
		text_view2(Widget::Layout::Gravity::WINDOW_CENTER);
		text_view3(Widget::Layout::Gravity::WINDOW_LEFT);
		text_view4(Widget::Layout::Gravity::WINDOW_RIGHT);
		text_view5(Widget::Layout::Gravity::WINDOW_TOP);
		text_view6(Widget::Layout::Gravity::WINDOW_BOTTON);
	}
private:
	Widget::TextView text_view1{m_ui, get_title()};
	Widget::TextView text_view2{m_ui, get_title(), Font::Size::_36px};
	Widget::TextView text_view3{m_ui, get_title(), Font::Size::_36px};
	Widget::TextView text_view4{m_ui, get_title(), Font::Size::_36px};
	Widget::TextView text_view5{m_ui, get_title(), Font::Size::_36px};
	Widget::TextView text_view6{m_ui, get_title(), Font::Size::_36px};
};
}