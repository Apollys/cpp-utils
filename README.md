# C++ Utility Functions

<br/>

<details>
  <summary><b>Vector ostream operator<<</b></summary><p>
  
```c++
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
```
</p></details><br/>

<br/>

<details>
  <summary><b>Simple struct with ostream operator<<</b></summary><p>
  
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
  <summary><b>Timer</b></summary><p>
  
```c++
#include <chrono>

class Timer {
  using high_res_clock = std::chrono::high_resolution_clock;

  private:
  high_res_clock::time_point start_time_point_;
  high_res_clock::time_point end_time_point_;
  double prev_duration_;
  bool running_;

  double ComputeDuration(high_res_clock::time_point start, high_res_clock::time_point end) {
    using DurationType = std::chrono::duration<double>;
    DurationType dur = std::chrono::duration_cast<DurationType>(end - start);
    return dur.count();
  }

  public:
  Timer() : prev_duration_(0), running_(true) {
    start_time_point_ = high_res_clock::now();
    end_time_point_ = high_res_clock::now();
  }

  // Resets and starts timer
  void Reset() {
    start_time_point_ = high_res_clock::now();
    prev_duration_ = 0;
    running_ = true;
  }

  void Pause() {
    end_time_point_ = high_res_clock::now();
    prev_duration_ += ComputeDuration(start_time_point_, end_time_point_);
    running_ = false;
  }

  // Restarts timer without resetting the total duration
  void Resume() {
    start_time_point_ = high_res_clock::now();
    running_ = true;
  }

  double GetSeconds() {
    if (running_) {
      return prev_duration_ + ComputeDuration(start_time_point_, high_res_clock::now());
    }
    return prev_duration_;
  }

};
```
</p></details><br/>

<br/>

<details>
  <summary><b>Simple integer RNG</b></summary><p>
  
```c++
#include <chrono>
#include <random>

namespace rng {

int CurrentTimeNano() {
  auto current_time = std::chrono::high_resolution_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(current_time).count();
}

template <typename IntType>
IntType SimpleIntRng(IntType min_value, IntType max_value) {
  static_assert(std::is_integral<IntType>::value, "Parameters must be of integral type");
  static std::default_random_engine engine(CurrentTimeNano());
  std::uniform_int_distribution<int> distribution(min_value, max_value);
  return distribution(engine);
}
  
} // namespace rng
```
</p></details><br/>

<br/>

<details>
  <summary><b>String whitespace trim</b></summary><p>
  
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

<details>
  <summary><b>String split</b></summary><p>
  
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
  <summary><b>String join</b></summary><p>
  
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
  <summary><b>Time Seed</b></summary><p>
  
```c++
#include <chrono>

int CurrentTimeNano() {
  auto current_time = std::chrono::high_resolution_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(current_time).count();
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Human-readable number formatting</b></summary><p>
  
```c++
#include <string>
#include <cstdlib>

std::string FormatNumber(int num) {
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
```
</p></details><br/>

<br/>
