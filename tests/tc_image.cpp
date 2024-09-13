#include <catch2/catch_test_macros.hpp>

#include "image.hpp"

CATCH_REGISTER_ENUM(App::Image::Format,
					App::Image::Format::None,
					App::Image::Format::RGBA,
					App::Image::Format::RGBA32F)

TEST_CASE("Image class")
{
	// Setup
	std::string filename = "./resources/morpheus.jpg";
	App::Image image{filename};
	int32_t width = 1920;
	int32_t height = 1080;

	SECTION("Load image from a file")
	{
		REQUIRE(image.ID() != 0);
		REQUIRE(image.get_width() == width);
		REQUIRE(image.get_height() == height);
		REQUIRE(image.get_label() == "morpheus");
	}

	SECTION("Resize a image")
	{
		const float factor = 0.80f;
		ImVec2 new_size = ImVec2((float)width * factor, (float)height * factor);

		image.resize(new_size);

		REQUIRE(image.get_width() == new_size.x);
		REQUIRE(image.get_size().x == new_size.x);
		REQUIRE(image.get_height() == new_size.y);
		REQUIRE(image.get_size().y == new_size.y);
	}

	SECTION("Load image from a file with a given size")
	{
		ImVec2 size{1280, 720};
		App::Image image1{filename, size};

		REQUIRE(image1.ID() != 0);
		REQUIRE(image1.get_width() == size.x);
		REQUIRE(image1.get_height() == size.y);
		REQUIRE(image1.get_label() == "morpheus");
	}

	SECTION("Invalid file name")
	{
		std::string invalid_filename = "logo.png";
		REQUIRE_THROWS_AS(App::Image{invalid_filename}, std::runtime_error);
	}

}




