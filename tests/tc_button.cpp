#include "fakeit.hpp"
#include <catch2/catch_test_macros.hpp>
#include "widgets/button.hpp"

using namespace fakeit;

TEST_CASE("Button class")
{
	std::string label0 = "btn0";
	ImVec2 size0{20.0f, 40.0f};
	ImVec2 position0{0.0f, 40.0f};
	App::Button btn0{label0, size0, position0, false, [&btn0]()
	{
		btn0.set_state(true);
	}};

	REQUIRE(btn0.get_id() == 0);
	REQUIRE(btn0.get_size().x == size0.x);
	REQUIRE(btn0.get_size().y == size0.y);
	REQUIRE(btn0.get_position().x == position0.x);
	REQUIRE(btn0.get_position().y == position0.y);
	REQUIRE(btn0.get_label() == label0);
	REQUIRE(btn0.get_state() == false);

	std::string label1 = "btn1";
	ImVec2 size1{10.0f, 30.0f};
	ImVec2 position1{20.0f, 50.0f};
	std::function<void()> callback1;
	App::Button btn1{label1, size1, position1, true, callback1};

	callback1 = [&]()
	{
		btn1.set_state(false);
	};

	REQUIRE(btn1.get_id() == 1);
	REQUIRE(btn1.get_size().x == size1.x);
	REQUIRE(btn1.get_size().y == size1.y);
	REQUIRE(btn1.get_position().x == position1.x);
	REQUIRE(btn1.get_position().y == position1.y);
	REQUIRE(btn1.get_label() == label1);
	REQUIRE(btn1.get_state() == true);
	btn1.set_state(false);
	REQUIRE(btn1.get_state() == false);

	Mock<App::Button> mockBtn0;
	auto callback3 = [&]()
	{ mockBtn0.get().toggle_state(); };
	When(Method(mockBtn0, render)).AlwaysDo(callback3);

	mockBtn0.get().operator()();
	REQUIRE(mockBtn0.get().get_state() == true);
	Verify(Method(mockBtn0, render)).Exactly(1);

	mockBtn0.get().operator()();
	REQUIRE(mockBtn0.get().get_state() == false);
	Verify(Method(mockBtn0, render)).Exactly(2);
}