#include "fakeit.hpp"
#include <catch2/catch_test_macros.hpp>
#include <utility>

#include "i_screen.hpp"
#include "logger.hpp"

using namespace fakeit;

namespace Core
{
class Screen1: public IScreen
{
public:
	Screen1(const std::string_view &title, const ImVec2 &size)
		: IScreen(title, size)
	{}
	void render() override
	{
		logger.debug("Render call");
	}

};
}

class FSM
{
public:
	//FSM definition
	enum class eSystemState
	{
		INVALID = -1, SCREEN1, SCREEN2, SCREEN3, SCREEN4, SCREEN5
	};
private:
	eSystemState m_current_state = eSystemState::INVALID;
	std::vector<std::unique_ptr<Core::IScreen>> m_FSM;

public:

	explicit FSM(eSystemState initial_state)
		: m_current_state(initial_state)
	{
		m_FSM.push_back(std::make_unique<Core::Screen1>("Screen1", ImVec2(1280, 720)));
	}

	void render()
	{
		if (!m_FSM.empty()) {
			m_FSM[static_cast<int32_t>(m_current_state)]->render();
		}
	}

	[[nodiscard]] inline eSystemState get_current_state() const
	{
		return m_current_state;
	}
	inline void set_current_state(eSystemState current_state)
	{
		m_current_state = current_state;
	}

};

TEST_CASE("FSM class")
{
	FSM fsm{FSM::eSystemState::SCREEN1};
	fsm.render();
	REQUIRE(fsm.get_current_state() == FSM::eSystemState::SCREEN1);
}
