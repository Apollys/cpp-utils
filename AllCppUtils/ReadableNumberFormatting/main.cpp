#include <iostream>

#include "format_number.hpp"

int main() {
  std::cout << FormatNumber(0) << std::endl;
  std::cout << FormatNumber(-1345365) << std::endl;
  
  std::cout << std::endl;
  std::cout << FormatNumber(7) << std::endl;
  std::cout << FormatNumber(45) << std::endl;
  std::cout << FormatNumber(385) << std::endl;
  std::cout << FormatNumber(3968) << std::endl;
  std::cout << FormatNumber(98534) << std::endl;
  std::cout << FormatNumber(453767) << std::endl;
  std::cout << FormatNumber(1942935) << std::endl;
  std::cout << FormatNumber(43264328) << std::endl;
  std::cout << FormatNumber(452316167) << std::endl;
  /*
  std::cout << FormatNumber(5327345205) << std::endl;
  std::cout << FormatNumber(23986756753) << std::endl;
  std::cout << FormatNumber(299449238475) << std::endl;
  std::cout << FormatNumber(6147724571147) << std::endl;
  */
  
  std::cout << std::endl << "2^32 - 1 = " << FormatNumber(4294967295) << std::endl;
  std::cout << std::endl << "2^64 - 1 = " << FormatNumber(18446744073709551615UL) << std::endl;
  
  std::cout << std::endl;
  std::cout << SciNotation(3.145, 2) << std::endl;
  std::cout << SciNotation(3145, 2) << std::endl;
  
  return 0;
}
