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
  <summary><b>String trim</b></summary><p>
  
```c++
#include <algorithm> // std::find_if
#include <cctype> // std::isspace
#include <string>

// Trim from left, in-place
static inline void Ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
    return !std::isspace(ch);
  }));
}

// Trim from right, in-place
static inline void Rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
    return !std::isspace(ch);
  }).base(), s.end());  // .base() gets forward iterator from reverse
}

// Trim from both sides, in-place
static inline void Trim(std::string &s) {
    Ltrim(s);
    Rtrim(s);
}

// Trim from left, makes copy
static inline std::string LtrimCopy(std::string s) {
  Ltrim(s);
  return s;
}

// Trim from right, makes copy
static inline std::string RtrimCopy(std::string s) {
  Rtrim(s);
  return s;
}

// Trim from both sides, makes copy
static inline std::string TrimCopy(std::string s) {
  Trim(s);
  return s;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>String split</b></summary><p>
  
```c++
#include <string>
#include <vector>

std::vector<std::string> SplitString(std::string input_string, const char delim,
                                     bool retain_empty = false) {
  std::vector<std::string> results;
  size_t start_i = 0;
  size_t found_i = 0; // dummy initialization to start while loop
  size_t len;
  while (found_i != std::string::npos) {
    found_i = input_string.find(delim, start_i);
    len = (found_i == std::string::npos) ? input_string.length() - start_i : found_i - start_i;
    if (len > 0) { // non-consecutive delimiters
      results.push_back(input_string.substr(start_i, found_i - start_i));
    }
    else if (retain_empty) {
      results.push_back(std::string(""));
    }
    start_i = found_i + 1;
  }
  return results;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>String join</b></summary><p>
  
```c++
#include <vector>
#include <string>

// Delimiter as char
std::string JoinStrings(const std::vector<std::string>& input_vector, const char delim) {
  std::string result("");
  for (unsigned int i = 0; i < input_vector.size(); i++) {
    result += input_vector[i];
    if (i + 1 < input_vector.size()) {
      result += delim;
    }
  }
  return result;
}

// Delimiter as string
std::string JoinStrings(const std::vector<std::string>& input_vector, const std::string& delim) {
  std::string result("");
  for (unsigned int i = 0; i < input_vector.size(); i++) {
    result += input_vector[i];
    if (i + 1 < input_vector.size()) {
      result += delim;
    }
  }
  return result;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Integer power function</b></summary><p>
  
```c++
#include <type_traits>

// Fast int power function, assumes exponent is non-negative
template <typename BaseType, typename ExpType>
BaseType IntPower(BaseType base, ExpType exponent) {
  static_assert(std::is_integral<BaseType>::value, "Integral type required for base");
  static_assert(std::is_integral<ExpType>::value, "Integral type required for exponent");
  BaseType result = 1;
  if (base < 0) {
    result *= (exponent & 1) ? -1 : 1;
    base *= -1;
  }
  while (exponent > 0) {
    if (exponent & 1) {
       result *= base;
    }
    // Now exponent is even
    exponent /= 2;
    base *= base;
  }
  return result;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Round to specified precision</b></summary><p>
  
```c++
#include <cmath> // std::round
#include <type_traits>

// Fast int power function, assumes exponent is non-negative
template <typename BaseType, typename ExpType>
BaseType IntPower(BaseType base, ExpType exponent) {
  static_assert(std::is_integral<BaseType>::value, "Integral type required for base");
  static_assert(std::is_integral<ExpType>::value, "Integral type required for exponent");
  BaseType result = 1;
  if (base < 0) {
    result *= (exponent & 1) ? -1 : 1;
    base *= -1;
  }
  while (exponent > 0) {
    if (exponent & 1) {
       result *= base;
    }
    // Now exponent is even
    exponent /= 2;
    base *= base;
  }
  return result;
}

template <typename FloatType>
FloatType RoundToPrecision(FloatType value, int precision) {
  static_assert(std::is_floating_point<FloatType>::value, "Float type required for value");
  FloatType scale_factor = static_cast<FloatType>(IntPower(10, precision));
  return std::round(value * scale_factor) / scale_factor;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Scientific notation</b></summary><p>
  
```c++
#include <iomanip> // std::setprecision
#include <sstream>
#include <string>
#include <type_traits>
  
// Returns std::string containg scientific notation with given precision, float version
template <typename FloatType>
typename std::enable_if<std::is_floating_point<FloatType>::value, std::string>::type
SciNotation(FloatType value, int precision = 3) {
  std::stringstream ss;
  ss << std::scientific << std::setprecision(precision) << value;
  return ss.str();
}

// Returns std::string containg scientific notation with given precision, int version
template <typename IntType>
typename std::enable_if<std::is_integral<IntType>::value, std::string>::type
SciNotation(IntType value, int precision = 3) {
  return SciNotation(static_cast<double>(value), precision);
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Human-readable number formatting (To Be Updated)</b></summary><p>
  
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
