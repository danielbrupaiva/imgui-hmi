#pragma once

#include <random>
#include <sstream>
#include <iomanip>
#include <string>
#include <regex>

namespace Core::UUID {
  static std::string generate_uuid_v4() {
      // Random number generators
      std::random_device random_device;
      std::mt19937 generator(random_device());
      std::uniform_int_distribution<uint32_t> dist(0, 0xFFFFFFFF);

      // String stream for formatting
      std::stringstream ss;
      // Generate each segment of the UUID
      ss << std::hex << std::nouppercase;
      // First segment: 8 characters
      ss << std::setw(8) << std::setfill('0') << dist(generator) << "-";
      // Second segment: 4 characters
      ss << std::setw(4) << std::setfill('0') << (dist(generator) & 0xFFFF) << "-";
      // Third segment: 4 characters with version 4
      ss << std::setw(4) << std::setfill('0') << ((dist(generator) & 0x0FFF) | 0x4000) << "-";
      // Fourth segment: 4 characters with variant 1
      ss << std::setw(4) << std::setfill('0') << ((dist(generator) & 0x3FFF) | 0x8000) << "-";
      // Fifth segment: 12 characters split into two 6-character parts
      uint32_t part1 = dist(generator);
      uint32_t part2 = dist(generator);
      ss << std::setw(6) << std::setfill('0') << (part1 >> 8); // Use the top 24 bits
      ss << std::setw(6) << std::setfill('0') << (part2 & 0xFFFFFF); // Use the bottom 24 bits

      return ss.str();
    }
    static bool is_valid_uuid_v4(const std::string& uuid)
    {
      std::regex uuid_regex("^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-4[0-9a-fA-F]{3}-[89a-b][0-9a-fA-F]{3}-[0-9a-fA-F]{12}$");
      return std::regex_match(uuid, uuid_regex);
    }
} // Core::Utils