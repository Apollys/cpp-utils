#include <iostream>
#include <string>
#include <vector>

#include "string_join.hpp"
#include "string_split.hpp"

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  os << "[";
  for (size_t i = 0; i < v.size(); ++i) {
    os << v[i];
    if (i + 1 < v.size()) {
      os << ", ";
    }
  }
  os << (v.size() ? "]" : " ]");
  return os;
}

// Specialization for vector of strings
std::ostream& operator<<(std::ostream& os, const std::vector<std::string> v) {
  os << "[";
  for (size_t i = 0; i < v.size(); ++i) {
    os << "\"" << v[i] << "\"";
    if (i + 1 < v.size()) {
      os << ", ";
    }
  }
  os << "]";
  return os;
}

int main() {
  std::string s("The-quick--brown-fox----");
  std::cout << "s: " << s << std::endl;
  std::vector<std::string> results(SplitString(s, '-'));
  // std::cout << "split: " << SplitString(s, '-') << std::endl;
  std::cout << "split: " << results << std::endl;
  
  std::cout << std::endl << std::endl;
  
  std::cout << JoinStrings(SplitString(s, '-', true), '-') << std::endl;
  std::cout << JoinStrings(SplitString(s, '-', true), "_*_") << std::endl;
  std::cout << JoinStrings(SplitString(s, '-', false), ' ') << std::endl;
  
  return 0;
}
