#include <catch2/catch_test_macros.hpp>
#include "fakeit.hpp"

#include "sqlite.hpp"

using namespace fakeit;

TEST_CASE("SQLite class") {

    Core::Database::Spec spec;
    Core::Database::SQLite sqlite{spec};

    REQUIRE(sqlite.get_spec().dbname == "test.db");
    REQUIRE(sqlite.get_spec().host == "localhost");
    REQUIRE(sqlite.get_spec().port == 5432);
    REQUIRE(sqlite.get_spec().username == "admin");
    REQUIRE(sqlite.get_spec().password == "1234");
    REQUIRE(sqlite.is_open() == true);

    REQUIRE_THROWS(sqlite.check_error(SQLITE_FAIL, "Fail"));
    REQUIRE_THROWS(sqlite.check_error(SQLITE_ERROR, "Error"));

    const std::string CREATE_TABLE = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT);";
    const std::string INVALID_SQL = "SELECT FROM users;";
    REQUIRE(sqlite.exec_query(CREATE_TABLE) == SQLITE_OK);
    REQUIRE_THROWS(sqlite.exec_query(INVALID_SQL));

    sqlite.shutdown();
    REQUIRE_THROWS(sqlite.exec_query(CREATE_TABLE));
}
