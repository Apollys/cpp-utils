# C++ Miscellanious Utility Functions

<br/>

<details>
  <summary><b>Vector ostream operator<<</b></summary><p>
  
```c++
#include <ostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  os << "[ ";
  for (size_t i = 0; i + 1 < v.size(); i++) {
    os << v[i] << ", ";
  }
  if (v.size() > 0) {
    os << v[v.size() - 1] << " ";
  }
  os << "]";
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

<details>
  <summary><b>Trimming Whitespace<<</b></summary><p>
  
```c++
#include <algorithm> 
#include <cctype>
#include <string>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}
```
</p></details><br/>

<br/>

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

<details>
  <summary><b>Simple Struct with ostream operator<<</b></summary><p>
  
```c++
#include <ostream>

struct ValueIndexPair {
  int value = -1;
  int index = -1;
};

std::ostream& operator<<(std::ostream& os, const ValueIndexPair p) {
  os << "(" << p.value << ", " << p.index << ")";
  return os;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Random Number Generation</b></summary><p>
  
```c++
#include <functional>
#include <random>

void RngDemo() {
  std::default_random_engine engine;
  std::uniform_int_distribution<int> distribution(0, 100);
  std::function<int()> rng = std::bind(distribution, engine);
  // Now call rng() whenever we need a random value
  int random_value = rng();
}
```
</p></details><br/>

<br/>

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

<br/>

<details>
  <summary><b>Timer</b></summary><p>
  
```c++
#include <chrono>

class Timer {

  private:
  std::chrono::system_clock::time_point start_time_point;
  std::chrono::system_clock::time_point end_time_point;
  float prev_duration;
  int running = 0;

  public:
  Timer() {
    start_time_point = std::chrono::system_clock::now();
    end_time_point = std::chrono::system_clock::now();
    prev_duration = 0;
    running = 1;
  }

  void start() {
    start_time_point = std::chrono::system_clock::now();
    prev_duration = 0;
    running = 1;
  }

  void stop() {
    end_time_point = std::chrono::system_clock::now();
    std::chrono::duration<float> dur = end_time_point - start_time_point;
    prev_duration += dur.count();
    running = 0;
  }

  /* resume(): restart timer without resetting the total duration */
  void resume() {
    start_time_point = std::chrono::system_clock::now();
    running = 1;
  }

  float get_seconds() {
    if (running) {
      std::chrono::duration<float> dur =
                std::chrono::system_clock::now() - start_time_point;
      return dur.count() + prev_duration;
    }
    return prev_duration;
  }

};
```
</p></details><br/>

<br/>

<details>
  <summary><b>Human-Readable Number Formatting</b></summary><p>
  
```c++
#include <string>
#include <cstdlib>

std::string format_number(int num) {
	// First multiply by 10 to get one decimal place
	num *= 10;
	char SUFFIXES[] = {'K', 'M', 'B'};
	int suff_idx = -1;
	while(num >= 10000) {
	  num /= 1000;
		suff_idx++;
	}
	int int_part = num/10;
	int dec_part = num%10;
	std::string s = std::to_string(int_part);
	if (dec_part && (s.length() < 3)) {
	  s += "." + std::to_string(dec_part);
  }
	if (suff_idx >= 0) {
	  s += std::string(" ") + SUFFIXES[suff_idx];
  }
	return s;
}
</p></details><br/>

<br/>
