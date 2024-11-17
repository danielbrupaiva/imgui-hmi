#include <catch2/catch_test_macros.hpp>
#include "fakeit.hpp"

#include "sqlite.hpp"

using namespace fakeit;

TEST_CASE("SQLite class") {
    Core::Database::Spec spec{"test.db","admin", "1234", "localhost", 5432};
    Core::Database::SQLite sqlite{spec};

    REQUIRE(sqlite.get_spec().dbname == "test.db");
    REQUIRE(sqlite.get_spec().host == "localhost");
    REQUIRE(sqlite.get_spec().port == 5432);
    REQUIRE(sqlite.get_spec().username == "admin");
    REQUIRE(sqlite.get_spec().password == "1234");
    REQUIRE(sqlite.is_open() == true);

    REQUIRE_THROWS(sqlite.check_error(SQLITE_FAIL, "Fail"));
    REQUIRE_THROWS(sqlite.check_error(SQLITE_ERROR, "Error"));

    const std::string INVALID_SQL = "SELECT FROM tb_users;";
    const std::string DROP_TABLE_IF_EXIT = "DROP TABLE IF EXISTS tb_users;";
    const std::string CREATE_TABLE = "CREATE TABLE IF NOT EXISTS tb_users (id INTEGER PRIMARY KEY, name TEXT NOT NULL UNIQUE, type INTEGER NOT NULL);";
    const std::string READ_USER_INFO = fmt::format("SELECT * FROM tb_users WHERE name=\"USER#1\";");

    struct User {
        uint8_t id = 1;
        std::string name = "USER#1";
        uint8_t type = 2;
    };
    User user;
    const std::string INSERT_USER_AT_TABLE = fmt::format("INSERT INTO tb_users (id, name, type) VALUES ('{}','{}','{}');", std::to_string(user.id), user.name, user.type);

    SECTION("EXEC SIMPLE QUERY") {
        REQUIRE_THROWS(sqlite.query(INVALID_SQL));
        REQUIRE(sqlite.query(DROP_TABLE_IF_EXIT) == SQLITE_OK);
        REQUIRE(sqlite.query(CREATE_TABLE) == SQLITE_OK);
        REQUIRE(sqlite.query(INSERT_USER_AT_TABLE) == SQLITE_OK);
        REQUIRE(sqlite.query(READ_USER_INFO) == SQLITE_OK);
    }

    SECTION("EXEC RETURN QUERY") {

        REQUIRE_THROWS(sqlite.exec_query(INVALID_SQL));
        auto results = sqlite.exec_query(DROP_TABLE_IF_EXIT);
        REQUIRE(results.first == SQLITE_OK);
        REQUIRE(results.second.empty());
        results = sqlite.exec_query(CREATE_TABLE);
        REQUIRE(results.first == SQLITE_OK);
        REQUIRE(results.second.empty());
        results = sqlite.exec_query(INSERT_USER_AT_TABLE);
        REQUIRE(results.first == SQLITE_OK);
        REQUIRE(results.second.empty());
        results = sqlite.exec_query(READ_USER_INFO);
        REQUIRE(results.first == SQLITE_OK);
        REQUIRE(results.second[0]["id"] == std::to_string(user.id));
        REQUIRE(results.second[0]["name"] == user.name);
        REQUIRE(results.second[0]["type"] == std::to_string(user.type));
    }

    REQUIRE(sqlite.is_open() == true);
    REQUIRE(sqlite.close() == SQLITE_OK);
    REQUIRE(sqlite.is_open() == false);
    REQUIRE_THROWS(sqlite.query(CREATE_TABLE));

    REQUIRE(sqlite.is_open() == false);
    sqlite.open();
    REQUIRE(sqlite.is_open() == true);
    REQUIRE(sqlite.query(CREATE_TABLE) == SQLITE_OK);

}
