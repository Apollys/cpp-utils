#include <cmath>
#include <cstdlib> // std::to_string
#include <iomanip> // std::setprecision
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Generate string representing a float rounded to given number of significant figures
template <typename FloatType>
std::string FloatToSigFigs(FloatType value, int sig_figs) {
  static_assert(std::is_floating_point<FloatType>::value, "Float type required");
  int digits_before_decimal = (value > 1) ? std::floor(std::log10(value)) + 1 : 1;
  std::stringstream ss;
  ss << std::fixed << std::setprecision(sig_figs - digits_before_decimal) << value;
  return ss.str();
}  

template <typename IntType>
std::string IntSciNotation(IntType value, int sig_figs) {
  static_assert(std::is_integral<IntType>::value, "Integral type required");
  std::stringstream ss;
  ss << std::scientific << std::setprecision(sig_figs - 1) << static_cast<double>(value);
  return ss.str();
}

int main() {
  std::cout << FloatToSigFigs(123.45678, 3) << std::endl;
  std::cout << IntSciNotation(12345678, 3) << std::endl;
  std::cout << IntSciNotation(1000000, 3) << std::endl;
  std::cout << FloatToSigFigs(1.0, 3) << std::endl;
  std::cout << FloatToSigFigs(10.0, 3) << std::endl;
  std::cout << FloatToSigFigs(100.0, 5) << std::endl;
  
  return 0;
}
