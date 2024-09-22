#include "fakeit.hpp"
#include <catch2/catch_test_macros.hpp>
#include "text_view.hpp"

using namespace fakeit;

TEST_CASE("TextView class")
{
	SECTION("")
	{
		auto label1 = "TEXT#1";
		ImVec2 position{25.0f, 50.0f};
		auto font_size = static_cast<int8_t>(App::IMGUI::FontSize::_22px);

		App::TextView text_view1(label1);
		REQUIRE(text_view1.get_label() == label1);
		REQUIRE(text_view1.get_id() == 0);

		auto label2 = "TEXT#2";
		App::TextView text_view2(label2, font_size, position);
		REQUIRE(text_view2.get_label() == label2);
		REQUIRE(text_view2.get_position().x == position.x);
		REQUIRE(text_view2.get_position().y == position.y);
		REQUIRE(text_view2.get_id() == 1);
	}
}