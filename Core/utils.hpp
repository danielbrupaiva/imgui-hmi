#pragma once

// Macro for maximum of two values
#define MAX(x, y) ((x) > (y) ? (x) : (y))
// Macro for minimum of two values
#define MIN(x, y) ((x) < (y) ? (x) : (y))
// Macro for average of two values
#define AVG(x, y) (((x) + (y)) / 2)

#define TOGGLE(var) (var = ! var)
#define NOT(expr) (!(expr))
#define AND(a, b) ((a) && (b))
#define OR(a, b)  ((a) || (b))

namespace Core
{
class Utils
{

};
} // Core