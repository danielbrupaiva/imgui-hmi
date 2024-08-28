#pragma once

#include <iostream>
#include "imgui.hpp"

namespace App
{

class IScreen {
 public:
  IScreen (uint32_t id, const std::string &title, const ImVec2 &size) : id (id), title (title), size (size)
  {}
  virtual void render() = 0;

 private:
  uint32_t 		id;
  std::string	title;
  ImVec2 		size;

 public:
  inline uint32_t get_id () const { return id; }
  inline void set_id (uint32_t id) { IScreen::id = id; }
  inline const std::string &get_title () const { return title; }
  inline void set_title (const std::string &title) { IScreen::title = title; }
  inline const ImVec2 &get_size () const { return size; }
  inline void set_size (const ImVec2 &size) { IScreen::size = size; }
};

} // App