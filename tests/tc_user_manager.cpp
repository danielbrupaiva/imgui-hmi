#include <catch2/catch_test_macros.hpp>
#include "fakeit.hpp"
#include <bcrypt.h>
#include "user_manager.hpp"

using namespace fakeit;
using namespace Core;

TEST_CASE("User Manager")
{
    // Setup
    Database::Spec spec{"database.db"};
    Database::SQLite db{std::move(spec)};
    UserManager user_manager(db);

    // Reset table if exit
    user_manager.drop_if_exit_user_table();
    user_manager.init();

    // Add New Users
    User user1{"user#1", "1234"};
    User user2{"user#2", "1234"};
    User user3{"user#3", "1234"};
    User user4{"user#4", "1234"};
    User admin{"admin", "admin", User::SecurityLevel::ADMIN};
    User supervisor{"supervisor", "supervisor", User::SecurityLevel::SUPERVISOR};
    REQUIRE(user_manager.add_user(user1) == true);
    REQUIRE(user_manager.add_user(user2) == true);
    REQUIRE(user_manager.add_user(user3) == true);
    REQUIRE(user_manager.add_user(user4) == true);
    REQUIRE(user_manager.add_user(admin) == true);
    REQUIRE(user_manager.add_user(supervisor) == true);
    REQUIRE(user_manager.login("user#1", "1234") == true);
    REQUIRE(user_manager.login("user#2", "1234") == true);
    REQUIRE(user_manager.login("user#3", "1234") == true);
    REQUIRE(user_manager.is_logged() == true);
    user_manager.logout();
    REQUIRE(user_manager.is_logged() == false);
    // Exception if user exit in table
    User new_root_user{"root", "1234"};
    REQUIRE_THROWS(user_manager.add_user(new_root_user));
    // Read User
    // User doesn't exit
    // Update User
    // Delete User
    REQUIRE(user_manager.login("user#3", "1234") == true);
    REQUIRE(user_manager.delete_user("user#3") == true);
    REQUIRE(user_manager.login("user#2", "1234") == true);
    REQUIRE(user_manager.delete_user("user#1") == false);
    REQUIRE(user_manager.login("admin", "admin") == true);
    REQUIRE(user_manager.delete_user("user#2") == true);
    REQUIRE(user_manager.login("supervisor", "supervisor") == true);
    REQUIRE(user_manager.delete_user("user#2") == true);
    REQUIRE(user_manager.login("root", "root") == true);
    REQUIRE(user_manager.delete_user("user#2") == true);
    user_manager.logout();

    // Login
    REQUIRE(user_manager.is_logged() == false);
    // User not exit at database
    // Wrong password
    REQUIRE(user_manager.login("root", "1234") == false);
    // Correct password
    REQUIRE(user_manager.login("root", "root") == true);
    REQUIRE(user_manager.is_logged() == true);
    // Logout
    user_manager.logout();
    REQUIRE(user_manager.is_logged() == false);


}
