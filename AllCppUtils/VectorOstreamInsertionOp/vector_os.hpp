#include <ostream>
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
