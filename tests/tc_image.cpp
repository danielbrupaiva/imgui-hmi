#include <catch2/catch_test_macros.hpp>
#include "fakeit.hpp"

using namespace fakeit;

#include "widgets/image.hpp"

CATCH_REGISTER_ENUM(Core::Image::Format,
					Core::Image::Format::None,
					Core::Image::Format::RGBA,
					Core::Image::Format::RGBA32F)

TEST_CASE("Image class")
{
	// Setup
	std::string filename = "./resources/morpheus.jpg";
	Core::Image image{filename};
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
		Core::Image image1{filename, size};

		REQUIRE(image1.ID() != 0);
		REQUIRE(image1.get_width() == size.x);
		REQUIRE(image1.get_height() == size.y);
		REQUIRE(image1.get_label() == "morpheus");
	}

	SECTION("Invalid file name")
	{
		std::string invalid_filename = "logo.png";
		REQUIRE_THROWS_AS(Core::Image{invalid_filename}, std::runtime_error);
	}

	SECTION("Render image")
	{
		Mock<App::Image> mockImage;
		Fake(Method(mockImage, render));
		auto &img = mockImage.get();
		img.operator()();
		img.operator()(ImVec2(100, 200));
		img.operator()(ImVec2(100, 200), ImVec2(50.0, 25.0));
		Verify(Method(mockImage, render)).Exactly(3);

		REQUIRE(img.get_width() == 100);
		REQUIRE(img.get_height() == 200);
		REQUIRE(img.get_position().x == 50.0);
		REQUIRE(img.get_position().y == 25.0);

	}
}




