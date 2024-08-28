#pragma once

#include <iostream>
#include "imgui.hpp"

namespace App
{

class IWidget
{
 public:
  IWidget (uint32_t id, const std::string &label, const ImVec2 &size, const ImVec2 &position)
	  : id (id), label (label), size (size), position (position)
  {}

 private:
    uint32_t        id;
    std::string     label;
    ImVec2          size;
  	ImVec2          position;

 public:
  inline uint32_t get_id () const { return id; }
  inline void set_id (uint32_t id) { IWidget::id = id; }
  inline const std::string &get_label () const { return label; }
  inline void set_label (const std::string &label) { IWidget::label = label; }
  inline const ImVec2 &get_size () const {	return size; }
  inline void set_size (const ImVec2 &size) { IWidget::size = size; }
  inline const ImVec2 &get_position () const {	return position; }
  inline void set_position (const ImVec2 &position)  { IWidget::position = position; }
};
} // App