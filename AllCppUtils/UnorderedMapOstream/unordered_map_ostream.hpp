#include <ostream>
#include <unordered_map>

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::unordered_map<K, V>& map) {
  os << "{ ";
  size_t count = 0;
  for (const std::pair<K, V>& item : map) {
    os << item.first << ": " << item.second;
    if (count + 1 < map.size()) {
      os << ", ";
    }
    ++count;
  }
  os << " }";
  return os;
}
