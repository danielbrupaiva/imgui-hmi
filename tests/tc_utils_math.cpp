#include <catch2/catch_test_macros.hpp>

#include "math.hpp"

TEST_CASE("Math utils class")
{
	using namespace Core;
	using namespace Utils;
	SECTION("Max of float variables")
	{
		float a = 1.0f;
		float b = 2.5f;
		REQUIRE(Math::MAX(a, b) == b);
		std::vector<float> vec = {3.5f, 8.2f, 1.1f, 10.9f, 5.7f};
		REQUIRE(Math::MAX(vec) == 10.9f);
	} SECTION("Max of uint32_t variables")
	{
		uint32_t c = 4;
		uint32_t d = 10;
		REQUIRE(Utils::Math::MAX(d, c) == d);
		std::vector<uint32_t> vec = {5, 2, 1, 9, 7};
		REQUIRE(Math::MAX(vec) == 9);
	}

	SECTION("Max of int32_t variables")
	{
		int32_t c = 4;
		int32_t d = -10;
		REQUIRE(Utils::Math::MAX(d, c) == c);
		std::vector<int32_t> vec = {-5, 2, -1, -9, -7};
		REQUIRE(Math::MAX(vec) == 2);
	}

	SECTION("Min of float variables")
	{
		float a = 1.0f;
		float b = 2.5f;
		REQUIRE(Utils::Math::MIN(a, b) == 1);
		std::vector<float> vec = {3.5f, 8.2f, 1.1f, 10.9f, 5.7f};
		REQUIRE(Math::MIN(vec) == 1.1f);
	} SECTION("Min of uint32_t variables")
	{
		uint32_t a = 4;
		uint32_t b = 10;
		REQUIRE(Utils::Math::MIN(b, a) == a);
		std::vector<uint32_t> vec = {5, 2, 1, 9, 7};
		REQUIRE(Math::MIN(vec) == 1);
	}

	SECTION("Min of int32_t variables")
	{
		int32_t a = 4;
		int32_t b = -10;
		REQUIRE(Utils::Math::MIN(b, a) == b);
		std::vector<int32_t> vec = {-5, 2, -1, -9, -7};
		REQUIRE(Math::MIN(vec) == -9);
	}
}