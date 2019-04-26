#include <iostream>

#include "round_to_precision.hpp"

int main() {
  std::cout << RoundToPrecision(-123.9, 0) << std::endl;
  std::cout << RoundToPrecision(-123.3, 0) << std::endl;
  std::cout << RoundToPrecision(123.3, 0) << std::endl;
  std::cout << RoundToPrecision(123.9, 0) << std::endl;
  std::cout << std::endl;
  
  std::cout << RoundToPrecision(123.472176, 1) << std::endl;
  std::cout << RoundToPrecision(-123.472176, 1) << std::endl;
  std::cout << RoundToPrecision(123.472176, 2) << std::endl;
  std::cout << RoundToPrecision(-123.472176, 3) << std::endl;
  std::cout << RoundToPrecision(-123.472176, 4) << std::endl;
  std::cout << RoundToPrecision(123.472176, 5) << std::endl;
  std::cout << RoundToPrecision(123.472176, 6) << std::endl;
  std::cout << RoundToPrecision(123.472176, 7) << std::endl;
  std::cout << RoundToPrecision(123.472176, 8) << std::endl;
  std::cout << RoundToPrecision(123.472176, 9) << std::endl;
  
  std::cout << std::endl;
  std::cout << RoundToPrecision(123.7, -2) << std::endl;
  
  return 0;
}
