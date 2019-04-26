#include <iostream>

#include "int_power.hpp"

int main() {
  std::cout << IntPower(4, 6) << std::endl;
  std::cout << IntPower(1, 2345634) << std::endl;
  std::cout << IntPower(2, 16) << std::endl;
  std::cout << IntPower(10, 6) << std::endl;
  std::cout << IntPower(-5, 2) << std::endl;
  std::cout << IntPower(-1, 4235) << std::endl;
  std::cout << IntPower(-45, 3) << std::endl;
  
  return 0;
}
