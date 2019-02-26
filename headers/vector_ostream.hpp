#ifndef VECTOR_OSTREAM_HPP
#define VECTOR_OSTREAM_HPP

#include <ostream>
#include <string>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  os << "[";
  for (size_t i = 0; i < v.size(); i++) {
    os << v[i];
    if (i + 1 < v.size()) {
      os << ", ";
    }
  }
  os << (v.size() ? "]" : " ]");
  return os;
}

// Specialization for vector of strings
std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& v) {
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

#endif  // VECTOR_OSTREAM_HPP

