#pragma once

#include <iostream>
#include <unordered_map>
#include <optional>

#include "user.hpp"
#include "sqlite.hpp"

namespace Core {

class UserManager {

    struct SQLQueries {
        static constexpr const char* INIT_TABLE = "CREATE TABLE IF NOT EXISTS tb_users ( id INTEGER PRIMARY KEY AUTOINCREMENT, \
                                                                                            uuid TEXT UNIQUE NOT NULL, \
                                                                                            username TEXT UNIQUE NOT NULL, \
                                                                                            security_level INTEGER CHECK (security_level IN (0, 1, 2, 3)) NOT NULL, \
                                                                                            password TEXT NOT NULL );";
        static constexpr const char* INSERT_ROOT_USER_IF_NOT_EXIT = "INSERT INTO tb_users (uuid, username, security_level, password) \
                                                                        SELECT '00000000-0000-0000-0000-000000000001', 'root', 0, '$2b$12$QMBLdNUp5og66mLFKtaoAuiDzpJDa/BvWxfyLVBaF0JpxYkPRqq1C' \
                                                                        WHERE NOT EXISTS ( SELECT 1 FROM tb_users WHERE username = 'root' );";
        // CREATE
        static constexpr const char* INSERT_USER = "INSERT INTO tb_users (uuid, username, security_level, password) VALUES ('{}','{}','{}','{}');";
        // READ
        static constexpr const char* READ_ALL_USERNAMES = "SELECT username FROM tb_users;";
        static constexpr const char* READ_ALL_USERNAMES_ORDERED = "SELECT username FROM tb_users ORDER BY username ASC;";
        static constexpr const char* READ_ALL_USERNAMES_ORDERED_ID = "SELECT username FROM tb_users ORDER BY user_id;";
        static constexpr const char* READ_USER_INFO = "SELECT * FROM tb_users WHERE username='{}';";
        // UPDATE
        static constexpr const char* UPDATE_USER = "UPDATE tb_users SET username='{}', security_level={}, password='{}' WHERE user_id=(SELECT user_id FROM tb_users WHERE username = '{}');";
        // DELETE
        static constexpr const char* DROP_USERS_TABLE_IF_EXIT = "DROP TABLE IF EXISTS tb_users;";
        static constexpr const char* DELETE_USER = "DELETE FROM tb_users WHERE username='{}';";
    };

public:
    ~UserManager() = default;
    explicit UserManager(Database::IDatabase& database) : m_db(database) {
        init();
    }

    UserManager(UserManager&&) = delete;
    UserManager(const UserManager&) = delete;
    UserManager& operator=(const UserManager&) = delete;
    UserManager& operator=(UserManager&&) = delete;

    bool login(const std::string_view username, const std::string_view password)
    {
        if (m_current_user.is_logged()) {
            m_current_user.logout();
        }

        read_user(username);

        return m_current_user.login(password);
    }

    void logout()
    {
        if (m_current_user.is_logged()) {
            m_current_user.logout();
        }
    }

    [[nodiscard]] bool is_logged() const
    {
        return m_current_user.is_logged();
    }

    [[nodiscard]] bool drop_if_exit_user_table() const
    {
        return m_db.query(SQLQueries::DROP_USERS_TABLE_IF_EXIT) == SQLITE_OK;
    }

    [[nodiscard]] bool init() const
    {
        int32_t rc = SQLITE_ERROR;
        // INIT TABLE
        rc = m_db.query(SQLQueries::INIT_TABLE);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Fail to init database");
        }
        // INSERT ROOT USER IF NOT EXIT
        rc = m_db.query(SQLQueries::INSERT_ROOT_USER_IF_NOT_EXIT);
        if (rc != SQLITE_OK) {
            throw std::runtime_error("Fail to insert root user at database");
        }
        return rc == SQLITE_OK;
    }

    [[nodiscard]] bool add_user(const User& user) const
    {
        auto rc = m_db.query(fmt::format(SQLQueries::INSERT_USER, user.uuid(), user.name(), static_cast<int8_t>(user.security_level()), user.hash_password()));
        return rc == SQLITE_OK;
    }

    bool read_user(const std::string_view username)
    {
        auto [rc, result] = m_db.exec_query(fmt::format(SQLQueries::READ_USER_INFO, username));
        if (rc == SQLITE_OK) {
            m_current_user.set_name(result[0].find("username")->second);
            m_current_user.set_password(result[0].find("password")->second);
            m_current_user.set_security_level(stoi(result[0].find("security_level")->second));
        }
        return rc == SQLITE_OK;
    }

    bool update_user(const User& user);

    [[nodiscard]] bool delete_user(const std::string_view username) const
    {
        int32_t rc = SQLITE_ERROR;
        if (m_current_user.is_logged() && (m_current_user.name() == username ||
                                            m_current_user.security_level() == User::SecurityLevel::ROOT ||
                                            m_current_user.security_level() == User::SecurityLevel::ADMIN ||
                                            m_current_user.security_level() == User::SecurityLevel::SUPERVISOR)) {
            rc = m_db.query(fmt::format(SQLQueries::DELETE_USER, username.data()));
        }
        return rc == SQLITE_OK;
    }

private:
    bool retrieve_users_table();

    [[nodiscard]] std::optional<std::string> get_hash_password(const std::string& username) const
    {
        auto [rc, result] = m_db.exec_query(fmt::format(SQLQueries::READ_USER_INFO, username));
        if (rc == SQLITE_OK) {
            return result[0].find("password")->second;
        }
        return std::nullopt;
    }

private:
    Database::IDatabase& m_db;
    User m_current_user;
};

} // Core
