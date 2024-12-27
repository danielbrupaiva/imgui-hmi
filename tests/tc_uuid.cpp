#include <catch2/catch_test_macros.hpp>
#include "fakeit.hpp"

#include "uuid.hpp"

using namespace fakeit;

TEST_CASE("UUID")
{
  SECTION("VALIDATE UUID v4 WITH CONTROLLED SAMPLE")
  { //Valid UUID v4 (external tool)
    REQUIRE(Core::UUID::is_valid_uuid_v4("caa8b54a-eb5e-4134-8ae2-a3946a428ec7") == true);
    REQUIRE(Core::UUID::is_valid_uuid_v4("b11c9be1-b619-4ef5-be1b-a1cd9ef265b7") == true);
    REQUIRE(Core::UUID::is_valid_uuid_v4("01bec7ba-dc02-49ae-ae39-29dfbcdd9198") == true);

    REQUIRE(Core::UUID::is_valid_uuid_v4("b5e0760d-8f5f-43e3-b3d2-00fb3074007f373b") == false);
    REQUIRE(Core::UUID::is_valid_uuid_v4("41cd6fe1-aa20-4c58-8885-006ca57500f83a9c") == false);
    REQUIRE(Core::UUID::is_valid_uuid_v4("ddb22dd6-b828-415f-ba48-0029f15a00756787") == false);
  }

  SECTION("GENERATE AND VALIDATE UUID v4")
  {
    for (auto i = 0; i < 30; i++) {
      auto uuid = Core::UUID::generate_uuid_v4();
      REQUIRE(Core::UUID::is_valid_uuid_v4(uuid) == true);
    }
  }
}
