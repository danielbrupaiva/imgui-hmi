#include <catch2/catch_test_macros.hpp>
#include "fakeit.hpp"

#include "user.hpp"

using namespace fakeit;

TEST_CASE("USERS")
{
    SECTION("CREATE USER")
    {// id, name, security_level, password, is_logged
        Core::User dummy{"root", Core::User::SecurityLevel::ROOT};
        REQUIRE(Core::UUID::is_valid_uuid_v4(dummy.uuid()));

        REQUIRE(dummy.name() == "root");
        dummy.set_name("user#1");
        REQUIRE(dummy.name() == "user#1");

        REQUIRE(dummy.security_level() == Core::User::SecurityLevel::ROOT);
        dummy.set_security_level(Core::User::SecurityLevel::USER);
        REQUIRE(dummy.security_level() == Core::User::SecurityLevel::USER);

        dummy.set_password("secret@1");
        REQUIRE(dummy.is_valid_password("secccret") == false);
        REQUIRE(dummy.is_valid_password("secret@1") == true);
        dummy.set_password("secret#2");
        REQUIRE(dummy.is_valid_password("secret") == false);
        REQUIRE(dummy.is_valid_password("secret#2") == true);

        REQUIRE(dummy.is_logged() == false);
        dummy.set_logged(dummy.is_valid_password("secret#2"));
        REQUIRE(dummy.is_logged() == true);
    }


    SECTION("CREATE IN USERS TABLE")
    {

    }
    SECTION("READ IN USERS TABLE")
    {

    }
    SECTION("UPDATE IN USERS TABLE")
    {

    }
    SECTION("DELETE IN USERS TABLE")
    {

    }
}