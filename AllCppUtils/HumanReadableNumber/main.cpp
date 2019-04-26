#include <iostream>

#include "human_readable_number.hpp"

template <typename IntType>
void TestHumanReadableFormat(IntType value) {
  std::cout << "Value: " << value << " -> " << HumanReadableFormat(value) << std::endl;
}

int main() {
  TestHumanReadableFormat(0);
  TestHumanReadableFormat(-1345365);
  
  std::cout << std::endl;
  TestHumanReadableFormat(7);
  TestHumanReadableFormat(45);
  TestHumanReadableFormat(385);
  TestHumanReadableFormat(3968);
  TestHumanReadableFormat(98534);
  TestHumanReadableFormat(453767);
  TestHumanReadableFormat(1942935);
  TestHumanReadableFormat(43264328);
  TestHumanReadableFormat(452316167);

  std::cout << std::endl;
  TestHumanReadableFormat(5327345205);
  TestHumanReadableFormat(23986756753);
  TestHumanReadableFormat(299449238475);
  TestHumanReadableFormat(-299449238475);
  TestHumanReadableFormat(6147724571147);

  
  std::cout << std::endl;
  std::cout << std::endl << "2^32 - 1 = " << HumanReadableFormat(4294967295) << std::endl;
  std::cout << std::endl << "2^64 - 1 = " << HumanReadableFormat(18446744073709551615UL) << std::endl;
  
  return 0;
}
