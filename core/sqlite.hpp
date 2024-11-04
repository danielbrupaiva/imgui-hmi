#pragma once

#include <iostream>
#include <sqlite3.h>
#include "logger.hpp"

namespace Core::Database {

    struct Spec {
        std::string dbname    = "test.db";
        std::string username   = "admin";
        std::string password  = "1234";
        std::string host      = "localhost";
        uint32_t port         = 5432;
    };

    class IDatabase {
    public:
        virtual ~IDatabase() = default;
        explicit IDatabase(Spec& spec) : m_spec(spec){}
        virtual int32_t init() = 0;
        virtual bool is_open() = 0;
        virtual void shutdown() = 0;
        virtual int32_t exec_query(std::string_view sql) = 0;
        virtual void check_error(int32_t result_code, std::string_view error_msg) = 0;

    //Getters and Setters
        [[nodiscard]] Spec get_spec() const {
            return m_spec;
        }
        void set_spec(const Spec &spec) {
            m_spec = spec;
        }

    protected:
        Spec m_spec;
    };

    class SQLite : public IDatabase {
    public:
        ~SQLite() override {
            SQLite::shutdown();
        };

        explicit SQLite(Spec &spec)
            : IDatabase(spec) {
            m_is_open = SQLite::init() == SQLITE_OK;
        }

        bool is_open() override {
            return m_conn && m_is_open;
        }

        int32_t exec_query(std::string_view sql) override {

            if(!is_open()) {
                throw std::runtime_error("SQLite database not open");
            }

            char* error_msg = nullptr;
            int32_t rc = sqlite3_exec(m_conn, sql.data(), nullptr, nullptr, &error_msg);
            SQLite::check_error(rc, fmt::format("SQLite::exec_query() not possible to execute query {} ", error_msg ? std::string(error_msg) : ""));
            sqlite3_free(error_msg);

            return rc;
        }

        void check_error(int32_t result_code, std::string_view error_msg) override {
            if (result_code != SQLITE_OK && result_code != SQLITE_DONE && result_code != SQLITE_ROW) {
                throw std::runtime_error(fmt::format("SQLite error: {} (Code: {})", error_msg, result_code));
            }
            logger.info("SQLite::check_error: SQLITE_API: {}", result_code == SQLITE_OK ? "SQLITE_OK" : std::to_string(result_code));
        }

        int32_t init() override {
            int32_t rc = sqlite3_open(m_spec.dbname.c_str(), &m_conn);
            SQLite::check_error(rc, "SQLite::init() DB not open");
            return rc;
        }

        void shutdown() override {
            if(!is_open()) {
                logger.error("SQLite::shutdown() DB not open");
                return;
            }
            int32_t rc = sqlite3_close(m_conn);
            SQLite::check_error(rc, "SQLite::close() DB closed");
            m_is_open = false;
        }

    private:
        sqlite3* m_conn{nullptr};
        bool m_is_open = false;
    };
} // Core

