#include <cmath>
#include <cstdlib> // std::to_string
#include <string>

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



template <typename IntType>
std::string FormatNumber(IntType num) {
  static_assert(std::is_integral<IntType>::value, "Integral type required");
  std::string s("");
  bool negative = num < 0;
  if (negative) {
    num = -num;
    s += '-';
  }
	// First multiply by 10 to get one decimal place
	num *= 10;
	char SUFFIXES[] = {'K', 'M', 'B', 'T'};
	const size_t num_suffixes = sizeof(SUFFIXES)/sizeof(SUFFIXES[0]);
	int suff_idx = -1;
	while(num >= 10000) {
	  num /= 1000;
		suff_idx++;
	}
	IntType int_part = num/10;
	IntType dec_part = num%10;
	s += std::to_string(int_part);
	if (dec_part && (s.length() < 3)) {
	  s += "." + std::to_string(dec_part);
  }
	if (suff_idx >= 0) {
	  s += std::string(" ") + SUFFIXES[suff_idx];
  }
	return s;
}
