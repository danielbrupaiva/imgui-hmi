#include <catch2/catch_test_macros.hpp>

#include "image.hpp"

CATCH_REGISTER_ENUM(Core::Image::Format,
					Core::Image::Format::None,
					Core::Image::Format::RGBA,
					Core::Image::Format::RGBA32F)

TEST_CASE("Image class")
{
	// Setup
	std::string filename = "/home/daniel/CLionProjects/cpp_template/resources/images/morpheus.jpg";
	Core::Image image{filename};
	int32_t width = 1920;
	int32_t height = 1080;

	SECTION("Load a image from memory")
	{
	}

	SECTION("Load image from a file")
	{
		REQUIRE(image.get_id() != 0);
		REQUIRE(image.get_width() == width);
		REQUIRE(image.get_height() == height);
		REQUIRE(image.get_label() == "morpheus");
	}

	SECTION("Load image from a file with a given size")
	{
		const float factor = 0.80f;
		float new_width = (float)width * factor;
		float new_height = (float)height * factor;

		Core::Image small_image{filename, ImVec2(new_width, new_height)};
		REQUIRE(small_image.get_id() != 0);
		REQUIRE(small_image.get_width() == new_width);
		REQUIRE(small_image.get_height() == new_height);
		REQUIRE(small_image.get_label() == "morpheus");
	}

	SECTION("Resize a image")
	{
		const float factor = 0.80f;
		const ImVec2 new_size{ImVec2((float)width * factor, (float)height * factor)};
		image.resize(new_size);
		REQUIRE(image.get_width() == static_cast<int32_t>(std::floor(new_size.x)));
		REQUIRE(image.get_height() == static_cast<int32_t>(std::floor(new_size.y)));
	}

}




