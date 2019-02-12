# C++ Utility Functions

<br/>

<details>
  <summary><b>Vector ostream operator<<</b></summary><p>
  
```c++
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

std::ostream& operator<<(std::ostream& os, const ValueIndexPair& p) {
  os << "(" << p.value << ", " << p.index << ")";
  return os;
}
```

```c++
struct Point {
  double x;
  double y;
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
  os << "(" << p.x << ", " << p.y << ")";
  return os;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Sort vector of pairs</b></summary><p>
  
```c++
// Explicitly declared lmabda types (c++11)
std::sort(pair_vector.begin(), pair_vector.end(),
          [](const std::pair<size_t, double>& left, const std::pair<size_t, double>& right) {
	    return left.second < right.second;
          });

// auto lambda types (c++14)
std::sort(pair_vector.begin(), pair_vector.end(), [](const auto& left, const auto& right) {
	    return left.second < right.second;
          });
```
</p></details><br/>

<br/>

<details>
  <summary><b>Generate random vector</b></summary><p>
  
```c++
#include "rng.hpp"

std::vector<int> GenerateRandomVector(size_t size, int min_value, int max_value) {
  UniformIntRng<int> rng(min_value, max_value);
  std::vector<int> generated_vector(size);
  for (size_t i = 0; i < size; ++i) {
    generated_vector[i] = rng.GenerateValue();
  }
  return generated_vector;
}
```
</p></details><br/>

<br/>

<details>
  <summary><b>Timer</b></summary><p>
  
  [Raw code](https://raw.githubusercontent.com/Apollys/cpp-utils/master/misc/timer.hpp)
  
```c++
#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
  using high_res_clock = std::chrono::high_resolution_clock;

 private:
  double prev_duration_;
  bool running_;
  high_res_clock::time_point start_time_point_;
  high_res_clock::time_point end_time_point_;

  double ComputeDuration(high_res_clock::time_point start, high_res_clock::time_point end) {
    using DurationType = std::chrono::duration<double>;
    DurationType dur = std::chrono::duration_cast<DurationType>(end - start);
    return dur.count();
  }

 public:
  Timer() : prev_duration_(0), 
            running_(true),
            start_time_point_(high_res_clock::now()) {}

  // Resets and starts timer
  void Reset() {
    prev_duration_ = 0;
    running_ = true;
    start_time_point_ = high_res_clock::now();
  }

  void Pause() {
    end_time_point_ = high_res_clock::now();
    prev_duration_ += ComputeDuration(start_time_point_, end_time_point_);
    running_ = false;
  }

  // Restarts timer without resetting the total duration
  void Resume() {
    running_ = true;
    start_time_point_ = high_res_clock::now();
  }

  double GetSeconds() {
    if (running_) {
      return prev_duration_ + ComputeDuration(start_time_point_, high_res_clock::now());
    }
    return prev_duration_;
  }

};

#endif  // TIMER_HPP

```
</p></details><br/>

<br/>

<details>
  <summary><b>RNG</b></summary><p>
  
  [Raw code](https://raw.githubusercontent.com/Apollys/cpp-utils/master/misc/rng.hpp)
  
```c++
#ifndef RNG_HPP
#define RNG_HPP

#include <chrono>
#include <random>

namespace rng_util {

int CurrentTimeNano() {
  auto current_time = std::chrono::high_resolution_clock::now().time_since_epoch();
  return std::chrono::duration_cast<std::chrono::nanoseconds>(current_time).count();
}

} // namespace rng_util

template <typename IntType>
class UniformIntRng {
 private:
  IntType min_value_;
  IntType max_value_;
  std::default_random_engine engine_;
  std::uniform_int_distribution<IntType> distribution_;

 public:
  UniformIntRng(IntType min_value, IntType max_value) : 
      min_value_(min_value), max_value_(max_value) {
    static_assert(std::is_integral<IntType>::value, "Requires integral type");
    engine_ = std::default_random_engine(rng_util::CurrentTimeNano());
    distribution_ = std::uniform_int_distribution<IntType>(min_value_, max_value_);
  }
  
  IntType GenerateValue() {
    return distribution_(engine_);
  }
};

template <typename FloatType>
class UniformFloatRng {
 private:
  FloatType min_value_;
  FloatType max_value_;
  std::default_random_engine engine_;
  std::uniform_real_distribution<FloatType> distribution_;

 public:
  UniformFloatRng(FloatType min_value, FloatType max_value) : 
      min_value_(min_value), max_value_(max_value) {
    static_assert(std::is_floating_point<FloatType>::value, "Requires floating point type");
    engine_ = std::default_random_engine(rng_util::CurrentTimeNano());
    distribution_ = std::uniform_real_distribution<FloatType>(min_value_, max_value_);
  }
  
  FloatType GenerateValue() {
    return distribution_(engine_);
  }
};

template <typename FloatType>
class NormalFloatRng {
 private:
  FloatType mean_;
  FloatType standard_deviation_;
  std::default_random_engine engine_;
  std::normal_distribution<FloatType> distribution_;

 public:
  NormalFloatRng(FloatType mean, FloatType standard_deviation) : 
      mean_(mean), standard_deviation_(standard_deviation) {
    static_assert(std::is_floating_point<FloatType>::value, "Requires floating point type");
    engine_ = std::default_random_engine(rng_util::CurrentTimeNano());
    distribution_ = std::normal_distribution<FloatType>(mean_, standard_deviation_);
  }
  
  FloatType GenerateValue() {
    return distribution_(engine_);
  }
};

template <typename IntType>
class NormalIntRng {
 private:
  double mean_;
  double standard_deviation_;
  std::default_random_engine engine_;
  std::normal_distribution<double> distribution_;

 public:
  NormalIntRng(double mean, double standard_deviation) : 
      mean_(mean), standard_deviation_(standard_deviation) {
    static_assert(std::is_integral<IntType>::value, "Template type must be integral");
    engine_ = std::default_random_engine(rng_util::CurrentTimeNano());
    distribution_ = std::normal_distribution<double>(mean_, standard_deviation_);
  }
  
  IntType GenerateValue() {
    return static_cast<IntType>(distribution_(engine_) + 0.5);
  }
};

class BernoulliRng {
 private:
  double true_probability_;
  std::default_random_engine engine_;
  std::uniform_real_distribution<double> distribution_;

 public:
  BernoulliRng(double true_probability) : true_probability_(true_probability) {
    engine_ = std::default_random_engine(rng_util::CurrentTimeNano());
    distribution_ = std::uniform_real_distribution<double>(0, 1);
  }
  
  double GenerateValue() {
    return distribution_(engine_) < true_probability_;
  }
};

#endif  // RNG_HPP

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
  <summary><b>Float To string given sig figs</b></summary><p>
  
```c++
#include <cmath> // std::log10
#include <type_traits>

// Generate string representing a float rounded to given number of significant figures
template <typename FloatType>
std::string FloatToSigFigs(FloatType value, int sig_figs) {
  static_assert(std::is_floating_point<FloatType>::value, "Float type required");
  int digits_before_decimal = (value > 1) ? std::floor(std::log10(value)) + 1 : 1;
  std::stringstream ss;
  ss << std::fixed << std::setprecision(sig_figs - digits_before_decimal) << value;
  return ss.str();
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
  <summary><b>Human-readable number formatting</b></summary><p>
  
```c++
#include <cmath> // std::log10
#include <cstdlib> // std::to_string
#include <iomanip> // std::setprecision
#include <sstream>
#include <string>
#include <vector>

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

// Generate string representing a float rounded to given number of significant figures
template <typename FloatType>
std::string FloatToSigFigs(FloatType value, int sig_figs) {
  static_assert(std::is_floating_point<FloatType>::value, "Float type required");
  int digits_before_decimal = (value > 1) ? std::floor(std::log10(value)) + 1 : 1;
  std::stringstream ss;
  ss << std::fixed << std::setprecision(sig_figs - digits_before_decimal) << value;
  return ss.str();
}  

template <typename IntType>
std::string IntSciNotation(IntType value, int sig_figs) {
  static_assert(std::is_integral<IntType>::value, "Integral type required");
  std::stringstream ss;
  ss << std::scientific << std::setprecision(sig_figs - 1) << static_cast<double>(value);
  return ss.str();
}

template <typename IntType>
std::string HumanReadableFormat(IntType num, int sig_figs = 3) {
  static_assert(std::is_integral<IntType>::value, "Integral type required");
  std::string result_string("");
  // First, check for negative values
  if (num < 0) {
    num = -num;
    result_string += '-';
  }
  // Next, check number's size
	static const std::vector<char> kSuffixChars{' ', 'K', 'M', 'B'};
  int log_scale = num ? std::floor(std::log10(num)) : 0;
  int k_log_scale = log_scale / 3;
  if (k_log_scale < 1) {
    return result_string + std::to_string(num);
  }
  else if (k_log_scale >= kSuffixChars.size()) {
    return result_string + IntSciNotation(num, sig_figs);
  }
  // Now, put into form {prefix-digits} + {suffix-char}
  double prefix_digits = static_cast<double>(num) / IntPower(1000, k_log_scale);
  result_string += FloatToSigFigs(prefix_digits, sig_figs);
  result_string += kSuffixChars[k_log_scale];
  return result_string;
}
```
</p></details><br/>

<br/>
