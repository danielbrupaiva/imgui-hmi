#pragma once

#include <random>
#include <sstream>
#include <iomanip>
#include <string>

namespace Core::UUID {
  static std::string generate()
  {
    // Random number generators
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);

    // String stream for formatting
    std::stringstream ss;

    // Generate each segment of the UUID
    ss << std::hex << std::nouppercase;
    ss << std::setw(8) << std::setfill('0') << dist(generator) << "-";
    ss << std::setw(4) << std::setfill('0') << (dist(generator) & 0xFFFF) << "-";
    ss << std::setw(4) << std::setfill('0') << ((dist(generator) & 0x0FFF) | 0x4000) << "-"; // Version 4
    ss << std::setw(4) << std::setfill('0') << ((dist(generator) & 0x3FFF) | 0x8000) << "-"; // Variant 1
    ss << std::setw(12) << std::setfill('0') << (static_cast<uint64_t>(dist(generator)) << 32 | dist(generator));

    return ss.str();
  }
} // Core::Utils