# C++ String Utility Functions

<br/>

<details>
  <summary><b>Vector to String</b></summary><p>
  
```c++
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
  <summary><b>Split String</b></summary><p>
  
```c++
#include <string>
#include <algorithm> // std::unique
#include <functional> // std::function

void split_string(std::string input_string, const char delim,
                  std::vector<std::string> &results, bool retain_empty = false) {
  // Remove consecutive groups of delim characters
  if (!retain_empty) {
    std::function<bool(const char &, const char &)> cmp_func = 
                [&delim] (const char &a, const char &b) { return (a == b) && (a == delim); };
    std::string::iterator new_end = std::unique(input_string.begin(), input_string.end(), cmp_func);
    input_string.erase(new_end, input_string.end());
  }
  // split into a vector
  results.clear();
  size_t start_i = 0;
  size_t found_i;
  bool done = false;
  while (!done) {
    found_i = input_string.find(delim, start_i);
    if (found_i != std::string::npos) {
      results.push_back(input_string.substr(start_i, found_i - start_i));
      start_i = found_i + 1;
    }
    else {
      results.push_back(input_string.substr(start_i, std::string::npos));
      done = true;
    }
  }
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Join String</b></summary><p>
  
```c++
#include <vector>
#include <string>

std::string join_strings(const std::vector<std::string> &input_vector, const std::string delim) {
  std::string result = "";
  for (unsigned int i = 0; i + 1 < input_vector.size(); i++) {
    result += input_vector[i] + delim;
  }
  if (input_vector.size() > 0) {
    result += input_vector[input_vector.size() - 1];
  }
  return result;
}
```
</p></details><br/>


