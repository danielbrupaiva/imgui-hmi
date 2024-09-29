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
		auto font_size = App::Font::Size::_36px;

		App::TextView text_view1(label1);
		REQUIRE(text_view1.get_label() == label1);

	}
}