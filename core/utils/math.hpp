#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <iterator>
#include <stdexcept>

#define TOGGLE(var) (var = ! var)
#define NOT(expr) (!(expr))
#define AND(a, b) ((a) && (b))
#define OR(a, b)  ((a) || (b))

namespace Core::Utils::Math
{
// Base case: single argument
template<typename Type>
constexpr Type MAX(Type value)
{ return value; }
// Recursive case: multiple arguments
template<typename Type, typename... Args>
constexpr Type MAX(Type first, Args... args)
{ return (first > MAX(args...)) ? first : MAX(args...); }
// Vector container
template<typename Type, typename... Args>
constexpr Type MAX(const std::vector<Type> &vec)
{ return *std::max_element(vec.begin(), vec.end()); }

template<typename Type>
static constexpr Type MIN(Type value)
{ return value; };

template<typename Type, typename... Args>
static constexpr Type MIN(Type first, Args... args)
{ return (first < MIN(args...)) ? first : MIN(args...); };

template<typename Type, typename... Args>
constexpr Type MIN(const std::vector<Type> &vec)
{ return *std::min_element(vec.begin(), vec.end()); }

template<typename Type>
static constexpr double AVG(Type value)
{ return static_cast<double>(value); };

template<typename Type, typename... Args>
static constexpr double AVG(Type first, Args... args)
{ return (static_cast<double>(first) + average_value(args...)) / (sizeof...(args) + 1); };
};