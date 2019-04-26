#include <type_traits>

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

