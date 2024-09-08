#include "widgets/i_widget.hpp"

namespace Core
{
class Button: public IWidget
{
	bool state = false;
	static uint32_t m_nextID;

public:
	Button(const std::string_view &label, const ImVec2 &size, const ImVec2 &position)
		: IWidget(label, static_cast<int32_t>(size.x), static_cast<int32_t>(size.y), position)
	{
		m_id = m_nextID++;
	}

	void operator()()
	{}

};
}

uint32_t Core::Button::m_nextID = 0;