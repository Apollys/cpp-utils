<details>
  <summary><b>Vector to String</b></summary><p>
  
```c++
#include <vector>
#include <string>
#include <sstream> // std::ostringstream

// General version
template <typename T>
std::string vtos(std::vector<T> v) {
  std::ostringstream oss;
  oss << "[ ";
  for (unsigned int i = 0; i + 1 < v.size(); i++) {
    oss << v[i] << ", ";
  }
  if (v.size() > 0) {
    oss << v[v.size() - 1] << " ";
  }
  oss << "]";
  return oss.str();
}

// Add quotes around strings (template specialization)
template <>
std::string vtos<std::string>(std::vector<std::string> v) {
  std::ostringstream oss;
  oss << "[ ";
  for (unsigned int i = 0; i + 1 < v.size(); i++) {
    oss << "\"" << v[i] << "\", ";
  }
  if (v.size() > 0) {
    oss << "\"" << v[v.size() - 1] << "\" ";
  }
  oss << "]";
  return oss.str();
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Unordered Map to String</b></summary><p>
  
```c++
#include <unordered_map>
#include <string>
#include <sstream> // std::ostringstream

template <typename K, typename V>
std::string mtos(std::unordered_map<K, V> map) {
  std::ostringstream oss;
  oss << "{ ";
  for (std::pair<K, V> item : map) {
    oss << item.first << ": " << item.second << ", ";
  }
  oss << "}";
  std::string s = oss.str();
  if (!map.empty()) s.erase(s.length() - 3, 1);
  return s;
}
```
</p></details><br/>

<br/>

