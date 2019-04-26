#include "unordered_map_ostream.hpp"

#include <iostream>
#include <unordered_map>

int main() {
  std::unordered_map<int, double> map;
  std::cout << map << std::endl;
  
  map[1] = 1.3;
  std::cout << map << std::endl;
  
  map[2] = 2.3;
  map[5] = 5.4;
  map[7] = 7.5;
  map[11] = 11.6;
  std::cout << map << std::endl;
  
  return 0;
}
