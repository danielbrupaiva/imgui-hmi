#pragma once

#include <iostream>

namespace Core::Database {
struct Spec {
    std::string dbname;
    std::string username;
    std::string password;
    std::string host;
    uint32_t port;
};
}