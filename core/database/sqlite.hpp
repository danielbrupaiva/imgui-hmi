#pragma once

#include <map>

#include "logger.hpp"
#include <sqlite3.h>

#include "connection_pool.hpp"

namespace Core::Database {

    class SQLQueries{
        public:
        SQLQueries() = delete;
        // CREATE
        inline static const std::string CREATE_USERS_TABLE = "CREATE TABLE IF NOT EXISTS tb_users (id INTEGER PRIMARY KEY, name TEXT NOT NULL UNIQUE, type INTEGER NOT NULL);";
        inline static const std::string INSERT_USER = "INSERT INTO tb_users (id, name, type) VALUES ('{}','{}','{}');";
        // READ
        inline static const std::string READ_ALL_USERNAMES = "SELECT username FROM tb_users;";
        inline static const std::string READ_ALL_USERNAMES_ORDERED = "SELECT username FROM tb_users ORDER BY username ASC;";
        inline static const std::string READ_ALL_USERNAMES_ORDERED_ID = "SELECT username FROM tb_users ORDER BY user_id;";
        inline static const std::string READ_USER_INFO = "SELECT * FROM tb_users WHERE name={};";
        // UPDATE
        inline static const std::string UPDATE_USER = "UPDATE tb_users SET username='{}', security_level={}, password='{}' WHERE user_id=(SELECT user_id FROM tb_users WHERE username = '{}');";
        // DELETE
        inline static const std::string DROP_USERS_TABLE_IF_EXIT = "DROP TABLE IF EXISTS tb_users;";
        inline static const std::string DELETE_USER = "DELETE FROM tb_users WHERE name={};";
    };

    struct Spec {
        std::string dbname;
        std::string username;
        std::string password;
        std::string host;
        uint32_t port;
    };

    class IDatabase {
    public:
        virtual ~IDatabase() = default;
        explicit IDatabase(const Spec& spec) : m_spec(spec){}
        virtual int32_t open() = 0;
        virtual bool is_open() = 0;
        virtual int32_t close() = 0;
        virtual int32_t query(std::string_view sql) = 0;
        virtual void check_error(int32_t result_code, std::string_view error_msg) = 0;

    //Getters and Setters
        [[nodiscard]] Spec spec() const {
            return m_spec;
        }
        void set_spec(const Spec &spec) {
            m_spec = spec;
        }

    private:
        Spec m_spec;
    };

    class SQLite : public IDatabase
    {
        using Row = std::map<std::string, std::string>;
        using ResultSet = std::vector<Row>;
    public:
        ~SQLite() override {
            SQLite::close();
        };

        explicit SQLite(const Spec &spec)
            : IDatabase(spec)
        {
            SQLite::open();
        }

        int32_t query(const std::string_view sql) override {
            std::lock_guard lock(m_mutex);
            if(!is_open()) {
                throw std::runtime_error("SQLite database not open");
            }

            char* error_msg = nullptr;
            int32_t rc = sqlite3_exec(m_conn, sql.data(), nullptr, nullptr, &error_msg);
            SQLite::check_error(rc,
                fmt::format("SQLite::exec() not possible to execute query {} ", error_msg ? std::string(error_msg) : "")
                );
            sqlite3_free(error_msg);

            return rc;
        }

        [[nodiscard]] std::pair<int32_t, std::vector<Row>> exec_query(const std::string_view sql) {
            std::lock_guard lock(m_mutex);
            int32_t rc = SQLITE_ERROR;
            sqlite3_stmt* stmt = nullptr;
            ResultSet results;

            rc = sqlite3_prepare_v2(m_conn, sql.data(), -1, &stmt, nullptr);
            SQLite::check_error(rc, fmt::format("Failed to prepare statement: {}", sqlite3_errmsg(m_conn)));

            const int column_count = sqlite3_column_count(stmt);
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                Row row;
                for (int index = 0; index < column_count; ++index) {
                    std::string col_name = sqlite3_column_name(stmt, index);
                    const auto col_value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, index));
                    row[col_name] = col_value ? col_value : "NULL";
                }
                results.emplace_back(row);
            }
            rc = sqlite3_finalize(stmt);
            SQLite::check_error(rc, fmt::format("Failed to finalize statement: {}", sqlite3_errmsg(m_conn)));
            return std::make_pair(rc, results);
        }

        void check_error(int32_t result_code, std::string_view error_msg) override {
            if (result_code != SQLITE_OK && result_code != SQLITE_DONE && result_code != SQLITE_ROW) {
                throw std::runtime_error(fmt::format("SQLite error: {} (Code: {})", error_msg, result_code));
            }
            logger.info("SQLite::check_error: {}", result_code == SQLITE_OK ? "SQLITE_OK" : std::to_string(result_code));
        }

        int32_t open() override {
            std::lock_guard lock(m_mutex);
            const auto rc = sqlite3_open(spec().dbname.c_str(), &m_conn);
            SQLite::check_error(rc, "SQLite::init() DB not open");
            return rc;
        }

        int32_t close() override {
            std::lock_guard lock(m_mutex);
            if(!is_open()) {
                logger.error("SQLite::shutdown() DB not open");
                return SQLITE_OK;
            }
            int32_t rc = sqlite3_close(m_conn);
            SQLite::check_error(rc, "SQLite::close() DB closed");
            m_conn = nullptr;
            return rc;
        }

        bool is_open() override {
            return m_conn != nullptr;
        }

    private:
        sqlite3* m_conn{nullptr};
        std::mutex m_mutex;
    };
} // Core

