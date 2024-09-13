#include "fakeit.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace fakeit;

#include "fsm.hpp"

TEST_CASE("FSM class")
{
	App::FSM fsm{App::FSM::eSystemState::SCREEN1};
	fsm.render();
	REQUIRE(fsm.get_current_state() == App::FSM::eSystemState::SCREEN1);
}
