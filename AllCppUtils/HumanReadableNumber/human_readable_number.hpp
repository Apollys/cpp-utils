#include <cmath> // std::log10
#include <cstdlib> // std::to_string
#include <iomanip> // std::setprecision
#include <sstream>
#include <string>
#include <vector>

// Fast int power function, assumes exponent is non-negative
template <typename BaseType, typename ExpType>
BaseType IntPower(BaseType base, ExpType exponent) {
  static_assert(std::is_integral<BaseType>::value, "Integral type required for base");
  static_assert(std::is_integral<ExpType>::value, "Integral type required for exponent");
  BaseType result = 1;
  if (base < 0) {
    result *= (exponent & 1) ? -1 : 1;
    base *= -1;
  }
  while (exponent > 0) {
    if (exponent & 1) {
       result *= base;
    }
    // Now exponent is even
    exponent /= 2;
    base *= base;
  }
  return result;
}

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

template <typename IntType>
std::string HumanReadableFormat(IntType num, int sig_figs = 3) {
  static_assert(std::is_integral<IntType>::value, "Integral type required");
  std::string result_string("");
  // First, check for negative values
  if (num < 0) {
    num = -num;
    result_string += '-';
  }
  // Next, check number's size
	static const std::vector<char> kSuffixChars{' ', 'K', 'M', 'B'};
  int log_scale = num ? std::floor(std::log10(num)) : 0;
  int k_log_scale = log_scale / 3;
  if (k_log_scale < 1) {
    return result_string + std::to_string(num);
  }
  else if (k_log_scale >= kSuffixChars.size()) {
    return result_string + IntSciNotation(num, sig_figs);
  }
  // Now, put into form {prefix-digits} + {suffix-char}
  double prefix_digits = static_cast<double>(num) / IntPower(1000, k_log_scale);
  result_string += FloatToSigFigs(prefix_digits, sig_figs);
  result_string += kSuffixChars[k_log_scale];
  return result_string;
}
