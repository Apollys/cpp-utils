#include <iostream>

#include "simple_int_rng.hpp"

int main() {
  for (int i = 0; i < 20; i += 3) {
    for (int k = 0; k < 10; ++k) {
      std::cout << rng::SimpleIntRng(0, i) << " ";
    }
    std::cout << std::endl;
  }
  
  return 0;
}
