<details>
  <summary><b>Vector ostream operator<<</b></summary><p>
  
```c++
#include <ostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  os << "[ ";
  for (size_t i = 0; i < v.size(); i++) {
    os << v[i];
    if (i + 1 < v.size()) {
      os << ", ";
    }
  }
  os << " ]";
  return os;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Unordered Map ostream operator<<</b></summary><p>
  
```c++
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
```
</p></details><br/>

<br/>

<details>
  <summary><b>Deque ostream operator<<</b></summary><p>
  
```c++
#include <ostream>
#include <deque>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::deque<T>& q) {
  os << "[ ";
  for (T el : q) {
    os << el << " ";
  }
  os << "]";
  return os;
}
```
</p></details><br/>

<br/>

