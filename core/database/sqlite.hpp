#pragma once

#include <map>

#include "logger.hpp"
#include "database.hpp"
#include <sqlite3.h>

namespace Core::Database {
    class SQLite : public IDatabase
    {
    public:
        ~SQLite() override {
            SQLite::close();
        };

        explicit SQLite(const Spec &&spec)
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

        std::pair<int32_t, std::vector<Row>> exec_query(const std::string_view sql) override {
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
            int32_t rc = SQLITE_ERROR;
            if(spec().dbname.empty()) {
                throw std::runtime_error("SQLite database not open");
            }
            rc = sqlite3_open(spec().dbname.c_str(), &m_conn);
            SQLite::check_error(rc, "SQLite::init() DB not open");
            return rc;
        }

        int32_t close() override {
            std::lock_guard lock(m_mutex);
            int32_t rc = SQLITE_ERROR;
            if(!is_open()) {
                logger.info("SQLite::shutdown() DB not open");
                return SQLITE_OK;
            }
            rc = sqlite3_close(m_conn);
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

