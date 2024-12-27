#pragma once

#include <iostream>
#include "spec.hpp"

namespace Core::Database {
struct IDatabase {
    using Row = std::map<std::string, std::string>;
    using ResultSet = std::vector<Row>;

    virtual ~IDatabase() = default;
    explicit IDatabase(const Spec& spec) : m_spec(spec){}
    IDatabase(const IDatabase&) = delete;
    IDatabase& operator=(const IDatabase&) = delete;
    IDatabase(IDatabase&&) = delete;
    IDatabase& operator=(IDatabase&&) = delete;

    virtual int32_t open() = 0;
    virtual bool is_open() = 0;
    virtual int32_t close() = 0;
    virtual int32_t query(std::string_view sql) = 0;
    virtual std::pair<int32_t, std::vector<Row>> exec_query(const std::string_view sql) = 0;
    virtual void check_error(int32_t result_code, std::string_view error_msg) = 0;

    //Getters and Setters
    [[nodiscard]] Spec spec() const {
        return m_spec;
    }

private:
    const Spec m_spec;
};
}
