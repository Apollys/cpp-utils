#include <iostream>
#include <string>

#include "string_trim.hpp"

int main() {
  std::string s("\t   Hello there\t Universe\n\t \t");

  std::cout << "-- Original string:" << std::endl << "[" << s << "]" << std::endl << std::endl;
  
  std::cout << "-- Copy trims:" << std::endl;
  std::cout << "[" << LtrimCopy(s) << "]" << std::endl;
  std::cout << "[" << RtrimCopy(s) << "]" << std::endl;
  std::cout << "[" << TrimCopy(s) << "]" << std::endl;
  std::cout << "-- Original string:" << std::endl << "[" << s << "]" << std::endl << std::endl;
  
  std::cout << "-- In-place trims:" << std::endl;
  std::string s2(s);
  std::cout << "[" << LtrimCopy(s2) << "]" << std::endl;
  s2 = std::string(s);
  std::cout << "[" << RtrimCopy(s2) << "]" << std::endl;
  s2 = std::string(s);
  std::cout << "[" << TrimCopy(s2) << "]" << std::endl;
  
  std::cout << "-- Original string:" << std::endl << "[" << s << "]" << std::endl << std::endl;
  return 0;
}
