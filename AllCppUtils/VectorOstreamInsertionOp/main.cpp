#include <iostream>
#include <vector>

#include "vector_os.hpp"

int main() {
  std::vector<char> char_vec;
  std::cout << char_vec << std::endl;
  
  std::vector<char> char_vec_2(4, 'a');
  char_vec_2.push_back('b');
  std::cout << char_vec_2 << std::endl;
  
  std::vector<int> int_vec{0, 1, 22, 33333, 765246, 2};
  std::cout << int_vec << std::endl;
  
  return 0;
}
