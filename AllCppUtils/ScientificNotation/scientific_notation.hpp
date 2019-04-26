#include <iomanip> // std::setprecision
#include <sstream>
#include <string>
#include <type_traits>
  
// Returns std::string containg scientific notation with given precision, float version
template <typename FloatType>
typename std::enable_if<std::is_floating_point<FloatType>::value, std::string>::type
SciNotation(FloatType value, int precision = 3) {
  std::stringstream ss;
  ss << std::scientific << std::setprecision(precision) << value;
  return ss.str();
}

// Returns std::string containg scientific notation with given precision, int version
template <typename IntType>
typename std::enable_if<std::is_integral<IntType>::value, std::string>::type
SciNotation(IntType value, int precision = 3) {
  return SciNotation(static_cast<double>(value), precision);
}
