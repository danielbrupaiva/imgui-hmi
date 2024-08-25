#pragma once

#include "logger.hpp"

using namespace Core;
namespace Global {
static Logger logger{"App", spdlog::level::debug};
};//namespace Global
