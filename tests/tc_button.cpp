#include <catch2/catch_test_macros.hpp>
#include "fakeit.hpp"

using namespace fakeit;

#include "button.hpp"
#include "widgets_wrapper.hpp"

TEST_CASE("Button class")
{
	Mock<App::IMGUI> mockIMGUI;
	auto &ui = mockIMGUI.get();
	When(Method(mockIMGUI, init)).Return(true);
	When(Method(mockIMGUI, shutdown)).AlwaysReturn();
	When(Method(mockIMGUI, setup_backend)).Return(true);
	When(Method(mockIMGUI, render)).AlwaysReturn();

	std::string label0{"btn0"};
	ImVec2 size0{100.0f, 50.0f};
	ImVec2 position0{32.0f, 48.0f};
	static bool state = false;

	Mock<App::IWidget> mockButton;
	When(Method(mockButton, render)).AlwaysReturn();
	// App::Widget::Button btn0{ui, label0, size0, position0, NULL};
	//
	// SECTION("btn0") {
	// 	REQUIRE(btn0.get_label() == label0);
	// 	REQUIRE(btn0.get_size().x == size0.x);
	// 	REQUIRE(btn0.get_size().y == size0.y);
	// 	REQUIRE(btn0.get_position().x == position0.x);
	// 	REQUIRE(btn0.get_position().y == position0.y);
	// 	REQUIRE(btn0.is_clicked() == false);
	//
	// 	btn0.toggle_state();
	// 	REQUIRE(btn0.is_clicked() == true);
	// 	btn0.set_state(false);
	// 	REQUIRE(btn0.is_clicked() == false);
	//
	// 	auto callback0 = [&]()
	// 	{
	// 		state = btn0.is_clicked();
	// 	};
	// 	btn0.set_callback(callback0);
	// 	btn0.get_callback().operator()();
	// 	REQUIRE(state == btn0.is_clicked());
	// }

	// SECTION("mockBtn0") {
	// 	Mock<App::Widget::Button> mock(btn0);
	// 	When(Method(mock, render)).AlwaysReturn();
	//
	// 	auto &mockBtn0 = mock.get();
	// 	mockBtn0.operator()();
	// 	Verify(Method(mock, render)).Once();
	//
	// 	mock.ClearInvocationHistory();
	//
	// 	ImVec2 new_size{123.0f, 456.0f};
	// 	ImVec2 new_position{789.0f, 1234.0f};
	// 	mockBtn0.operator()(new_size, new_position);
	// 	Verify(Method(mock, render)).Once();
	//
	// 	REQUIRE(mockBtn0.get_label() == "btn0");
	// 	REQUIRE(mockBtn0.get_size().x == new_size.x);
	// 	REQUIRE(mockBtn0.get_size().y == new_size.y);
	// 	REQUIRE(mockBtn0.get_position().x == new_position.x);
	// 	REQUIRE(mockBtn0.get_position().y == new_position.y);
	// }
	//
	// std::string label1{"btn1"};
	// ImVec2 size1{200.0f, 150.0f};
	// auto callback1 = [&]()
	// {
	// 	return false;
	// };
	//
	// App::Widget::Button btn1{label1, size1, callback1};
	//
	// SECTION("btn1") {
	// 	REQUIRE(btn1.get_label() == label1);
	// 	REQUIRE(btn1.get_size().x == size1.x);
	// 	REQUIRE(btn1.get_size().y == size1.y);
	// 	btn1.set_state(true);
	// 	REQUIRE(btn1.is_clicked() == true);
	//
	// 	btn1.toggle_state();
	// 	REQUIRE(btn1.is_clicked() == false);
	// 	btn1.set_state(false);
	// 	REQUIRE(btn1.is_clicked() == false);
	// }
}
